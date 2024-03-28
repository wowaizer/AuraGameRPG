#include "AuraProjectileSpell.h"
#include "AuraGameMain/Actor/AuraProjectile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameMain/Interaction/CombatInterface.h"
#include "AuraGameMain/AuraGameplayTags.h"




void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle,ActorInfo,ActivationInfo,TriggerEventData);

	
	
}

void UAuraProjectileSpell::SpawnProjectile(const FVector &ProjectileTargetLocation)
{
	//UKismetSystemLibrary::PrintString(this,FString("AcivateAbility C++"),true,true,FLinearColor::Red,3.f);

	
	const bool bIsServer =  GetAvatarActorFromActorInfo()->HasAuthority();
	if(!bIsServer) return;

	ICombatInterface *CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if(CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		AAuraProjectile *Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);
		
		const UAbilitySystemComponent* SourceASC = 
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

		const FGameplayEffectSpecHandle SpecHandle = 
		SourceASC->MakeOutgoingSpec(DamageEffecClass,GetAbilityLevel(),SourceASC->MakeEffectContext());
		

		const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

		const float ScaledDamage = Damage.GetValueAtLevel(15);  /*GetAbilityLevel()*/
		/*GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Red,FString::Printf(TEXT("Firebolt Damage %f"),ScaledDamage));*/

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,GameplayTags.Damage,ScaledDamage);
		Projectile->DamageEffectSpecHandle = SpecHandle;
	
		Projectile->FinishSpawning(SpawnTransform);
	}

}
