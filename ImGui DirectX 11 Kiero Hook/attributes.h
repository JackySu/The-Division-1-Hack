#pragma once

#define CONFIG_PATH ".\\config.ini"

#define AimChangeAccuracyRecoveryTimeMS 0
#define AimChangeModifier 1
#define AimChangeSensitivity 2
#define AimSpreadMax 3
#define AimSpreadMin 4
#define AirSupply 5
#define AirSupplyDepletionRate 6
#define AirSupplyRegenRate 7
#define AirSupplyRegenTickInterval 8
#define AirSupplyDepletionTickInterval 9
#define AirSupplyDamageRate 10
#define AirSupplyDamageInterval 11
#define AirSupplyEmptyDamageDelay 12
#define FallDamageMod 13
#define FallDamageLethalHeight 14
#define FallDamageStartHeight 15
#define BleedingOutHealth 16
#define BleedingOutHealthDegenRate 17
#define BleedingOutHealthDegenTickInterval 18
#define BleedingOutDieQuickMultiplier 19
#define BleedingOutReviveHealthPercentage 20
#define ClipSize 21
#define CoverAimSpreadMax 22
#define CoverAimSpreadMin 23
#define CoverSpreadMax 24
#define CoverSpreadMin 25
#define CriticalHitChanceResilience 26
#define DamageDoneToSuppressedTargetMod 27
#define DamageDoneToElitesMod 28
#define DamageMultiplierArms 29
#define DamageMultiplierBody 30
#define DamageMultiplierHead 31
#define DamageMultiplierLegs 32
#define DamageTakenMod 33
#define DamageTakenModBonus 34
#define DamageTakenFromElitesMod 35
#define NPCDamageDoneToPlayersMod 36
#define DownedDamageMax 37
#define DownedDamageMaxPVP 38
#define DownedDamageMod 39
#define DownedDamageModPVP 40
#define DownedHealth 41
#define DownedHealthDegenRate 42
#define DownedHealthDegenTickInterval 43
#define DownedInARowMax 44
#define DownedInARowMaxTimePeriod 45
#define DownedDieQuickMultiplier 46
#define DownedReviveHealthPercentage 47
#define TalentDownedAssistSpeedMod 48
#define TalentSecondChanceHealMod 49
#define TalentSecondChanceCooldown 50
#define FreeWeaponReloadChance 51
#define Health 52
#define HealthRegenDelay 53
#define HealthRegenExitCombatDelay 54
#define HealthRegenRate 55
#define HealthRegenTickInterval 56
#define HealthSegments 57
#define HorizontalRecoilBorderLeft 58
#define HorizontalRecoilBorderRight 59
#define HorizontalRecoilLeft 60
#define HorizontalRecoilRecoveryTimeMS 61
#define HorizontalRecoilRight 62
#define HorizontalRecoilTimeMS 63
#define IncomingHealingMod 64
#define OutgoingHealingMod 65
#define DarkZoneInventory 66
#define DefaultInventory 67
#define ResourceInventory 68
#define VanityInventory 69
#define BackupSpaceInventory 70
#define StashInventory 71
#define DarkZoneStashInventory 72
#define MailboxInventory 73
#define SurvivalStashInventory 74
#define DarkZoneInventoryFlatBonus 75
#define LifeOnKill 76
#define LootChanceMod 77
#define LootedAmmoMod 78
#define LootedGoldMod 79
#define LootMagicFind 80
#define ScavengingExtraDropChances 81
#define MeleeDamagePvP 82
#define MeleeDamage 83
#define MeleeDamageMitigationPercentage 84
#define MovementSpeedMod 85
#define NPCVisionRangeMod 86
#define PitchRecoveryPerSecond 87
#define PitchRecoveryPercent 88
#define PulseCriticalHitChance 89
#define PulseCriticalHitDamage 90
#define PVPDamageModifier 91
#define RPM 92
#define RangeLong 93
#define RangeMax 94
#define RangeOptimal 95
#define RecoilBase 96
#define RecoilClimbTimeMS 97
#define RecoilIncreasePerBullet 98
#define RecoilMax 99
#define RecoilMin 100
#define RecoilRecoveryPerSecond 101
#define RecoilRecoveryTimeMS 102
#define RecoilResetTimeMS 103
#define ReloadTimeMS 104
#define EmptyClipFirstRoundReloadTimeMS 105
#define InitialShellReloadTimeMS 106
#define RespawnTimeMS 107
#define RespawnMinimumTime 108
#define ReviveDurationMS 109
#define ReviveFromUnconsciousDurationMS 110
#define LootDeadBodyDurationMS 111
#define ReviveImmunityDuration 112
#define ReviveImmunityRange 113
#define ReviveServerNotifyTickIntervalMS 114
#define SurvivalSelfReviveMedkitCost 115
#define SurvivalUnconsciousReviveMedkitCost 116
#define SafetyBeltCooldown 117
#define SkillCriticalHitChance 118
#define SkillCriticalHitDamageMod 119
#define SkillHasteMod 120
#define SpreadIncreaseSpeed 121
#define SpreadIncreaseTimeMS 122
#define SpreadMax 123
#define SpreadMin 124
#define SpreadMovementMod 125
#define SpreadReductionSpeed 126
#define StaggerDamageModifier 127
#define StaminaConsumptionRate 128
#define StaminaConsumptionTickInterval 129
#define StaminaDamageTakenMod 130
#define Stamina 131
#define StaminaRegenDelay 132
#define StaminaRegenRate 133
#define StaminaRegenTickInterval 134
#define Suppression 135
#define TargetOutOfCoverDamageMod 136
#define ThrowRangeMod 137
#define TimeToMaxAccuracyMS 138
#define TimeToMinAccuracyMS 139
#define WeaponCriticalHitChance 140
#define WeaponCriticalHitDamageMod 141
#define WeaponCriticalHitChanceVsOOC 142
#define WeaponCriticalHitChanceWhileHipFiringMod 143
#define WeaponCriticalHitChanceCap 144
#define WeaponCriticalHitDamageFlatBonus 145
#define NormalizedWeaponCriticalHitDamageFlatBonus 146
#define WeaponDamageMultiplierHeadModBonus 147
#define WeaponDamageMultiplierHeadFlatBonus 148
#define NormalizedWeaponDamageMultiplierHeadFlatBonus 149
#define WeaponDrawSpeedMod 150
#define WeaponHolsterSpeedMod 151
#define WeaponRecoilKickModBonus 152
#define NormalizedWeaponRecoilKickModBonus 153
#define WeaponSwitchSpeedMod 154
#define XPMod 155
#define YawRecoveryPerSecond 156
#define YawRecoveryPercent 157
#define ZoneDiscoveryXP 158
#define PhysicalDamageMin 159
#define PhysicalDamageMax 160
#define PhysicalDamageVariation 161
#define BlastDamageMin 162
#define BlastDamageMax 163
#define BlastDamageVariation 164
#define BleedDamageMin 165
#define BleedDamageMax 166
#define BleedDamageVariation 167
#define BurnDamageMin 168
#define BurnDamageMax 169
#define BurnDamageVariation 170
#define ToxinDamageMin 171
#define ToxinDamageMax 172
#define ToxinDamageVariation 173
#define ElectricDamageMin 174
#define ElectricDamageMax 175
#define ElectricDamageVariation 176
#define NeutralDamageMin 177
#define NeutralDamageMax 178
#define NeutralDamageVariation 179
#define EMPDamageMin 180
#define EMPDamageMax 181
#define EMPDamageVariation 182
#define StaminaDamageMin 183
#define StaminaDamageMax 184
#define StaminaDamageVariation 185
#define DiseaseDamageMin 186
#define DiseaseDamageMax 187
#define DiseaseDamageVariation 188
#define ColdDamageMin 189
#define ColdDamageMax 190
#define ColdDamageVariation 191
#define TestDamageScaling 192
#define PrimaryOffensiveCalc 193
#define WeaponDamageModBonus 194
#define WeaponTypeDamageModCalc 195
#define NPCArmor 196
#define NPCArmorBypassRatioHead 197
#define NPCArmorBypassRatioBody 198
#define NPCArmorDamageModifier 199
#define NPCArmorBypassModifier 200
#define PhysicalDamageMitigationPercentage 201
#define BlastDamageMitigationPercentage 202
#define BleedDamageMitigationPercentage 203
#define BurnDamageMitigationPercentage 204
#define ToxinDamageMitigationPercentage 205
#define ElectricDamageMitigationPercentage 206
#define NeutralDamageMitigationPercentage 207
#define EMPDamageMitigationPercentage 208
#define StaminaDamageMitigationPercentage 209
#define PvPArmorDamageRatio 210
#define ArmorMitigationPercentageCalc 211
#define SelfSourceDamageMitigationPercentage 212
#define FriendlySourceDamageMitigationPercentage 213
#define NPCSourceDamageMitigationPercentage 214
#define OpponentSourceDamageMitigationPercentage 215
#define NullSourceDamageMitigationPercentage 216
#define WeaponMethodDamageMitigationPercentage 217
#define TrapMethodDamageMitigationPercentage 218
#define SkillMethodDamageMitigationPercentage 219
#define StatusEffectMethodDamageMitigationPercentage 220
#define MeleeMethodDamageMitigationPercentage 221
#define EnvironmentMethodDamageMitigationPercentage 222
#define BleedingStatusResistancePercentage 223
#define BlindDeafStatusResistancePercentage 224
#define BurningStatusResistancePercentage 225
#define ConfusedStatusResistancePercentage 226
#define DisruptedStatusResistancePercentage 227
#define ShockedStatusResistancePercentage 228
#define StaggeredStatusResistancePercentage 229
#define SuppressedStatusResistancePercentage 230
#define AimSwayMinHorizontal 231
#define AimSwayMaxHorizontal 232
#define AimSwayMinVertical 233
#define AimSwayMaxVertical 234
#define AimSwaySpeedModifier 235
#define VisualDetectionMod 236
#define VisualStealthMod 237
#define AudialDetectionMod 238
#define AudialStealthMod 239
#define DarkZoneItemsToDrop 240
#define DarkZoneItemsToDropRogue 241
#define DarkZoneConvertXPMod 242
#define DarkZoneXPMod 243
#define DarkZoneXPLossMod 244
#define DarkZoneXPLossRogueMod 245
#define DarkZoneXPLoss 246
#define DarkZoneXPLossRogue 247
#define ThreatPerBullet 248
#define ThreatTotalGeneratedMod 249
#define ThreatPerBulletDamageMod 250
#define SuppressionTriggerScore 251
#define SuppressionDefenseModifier 252
#define SuppressionDepletionRate 253
#define SuppressionDuration 254
#define SuppressionBufferScore 255
#define SuppressionBufferResetTime 256
#define StaggerGauge 257
#define StaggerAnimationDurationMod 258
#define ChanceOfGreenToBlueWhenCrafting 259
#define ChanceOfBlueToPurpleWhenCrafting 260
#define ChanceOfPurpleToOrangeWhenCrafting 261
#define XPRepeatableEventsMod 262
#define CreditsRepeatableEventsMod 263
#define SecurityRepeatableEventsMod 264
#define PersonnelRescueMissionsMod 265
#define SupplyDropMissionsMod 266
#define XPHeadshotKillsMod 267
#define XPTacticalKillsMod 268
#define XPSpecialKillsMod 269
#define XPEliteKillsMod 270
#define XPMultiKillsMod 271
#define XPKillsMod 272
#define XPAccoladeMod 273
#define ExtractionTimeMod 274
#define CraftingCostMod 275
#define SkillXPMod 276
#define DZRewardedCredsMod 277
#define VendorCostMod 278
#define AmmoDroppedMod 279
#define CreditsDroppedMod 280
#define LootedCreditsMod 281
#define LootedDZCreditsMod 282
#define UnlockedSkillSlots 283
#define SecondaryWeaponAllowedBool 284
#define RewardedCredsMod 285
#define PerkAutoDiscover 286
#define LastBulletDamageMod 287
#define SkillPowerModBonus 288
#define TalentGunslinger 289
#define TalentGunslingerBonusInc 290
#define TalentGunslingerBonusIncPvP 291
#define TalentGunslingerBonusDec 292
#define TalentGunslingerMaxBonus 293
#define TalentGunslingerBonusTimeDecrement 294
#define TalentGunslingerBonusTimeDecrementInterval 295
#define TalentClassifiedGunslinger 296
#define TalentClassifiedGunslingerBonusInc 297
#define TalentClassifiedGunslingerBonusIncPvP 298
#define TalentClassifiedGunslingerBonusDec 299
#define TalentClassifiedGunslingerMaxBonus 300
#define TalentClassifiedGunslingerBonusBonus 301
#define TalentClassifiedGunslingerBonus 302
#define TalentClassifiedGunslingerBonusTimeDecrement 303
#define TalentClassifiedGunslingerBonusTimeDecrementInterval 304
#define TalentClassifiedGunslingerTickRate 305
#define TalentClassifiedGunslingerPvPTickRate 306
#define TalentNomad 307
#define TalentClassifiedNomad 308
#define TalentClassifiedNomadDuration 309
#define TalentClassifiedNomadDefensiveBonus 310
#define TalentClassifiedNomadDiminishingReturnsDuration 311
#define TalentClassifiedNomadDiminishingReturns 312
#define TalentClassifiedNomadChanceForNoCooldown 313
#define TalentNomadCooldown 314
#define TalentNomadCooldownModifierOnPvPGameStart 315
#define TalentWarden 316
#define TalentWardenDamage 317
#define TalentWardenBonusInc 318
#define TalentWardenBonusIncFromSkillProxies 319
#define TalentWardenBonusDec 320
#define TalentWardenMaxBonus 321
#define TalentClassifiedWarden 322
#define TalentClassifiedWardenMaxBonus 323
#define TalentClassifiedWardenChance 324
#define TalentClassifiedWardenBonusResetModifier 325
#define TalentWeaponSwapReload 326
#define TalentSolo 327
#define TalentRiotShieldWithSMG 328
#define TalentHuntersFaith 329
#define TalentHuntersFaithBonusInc 330
#define TalentHuntersFaithMaxBonus 331
#define TalentHuntersFaithDuration 332
#define TalentClassifiedHuntersFaith 333
#define TalentClassifiedHuntersFaithMissedShotsAllowed 334
#define TalentPredatorsMark 335
#define TalentPredatorBleedCounter 336
#define TalentPredatorBleedDamage 337
#define TalentPredatorsMarkAdditionalPvPBleedDamageMod 338
#define TalentClassifiedPredatorsMark 339
#define TalentGlassHalfFull 340
#define TalentGlassHalfFullDuration 341
#define TalentGlassHalfFullBonus 342
#define TalentCoverShooter 343
#define TalentCoverShooterDuration 344
#define TalentCoverShooterMaxBonus 345
#define TalentCoverShooterBonusInc 346
#define TalentDevilsHeel 347
#define TalentDevilsHeelDuration 348
#define TalentDevilsHeelBothTalents 349
#define TalentFire 350
#define TalentFireBonusIncFromHeadshot 351
#define TalentFireBonusIncFromBodyshot 352
#define TalentFury 353
#define TalentFuryBonusIncFromWeakpoint 354
#define TalentFuryBonusIncFromEquipment 355
#define TalentClassifiedFireCrest 356
#define TalentClassifiedFireCrestBurnChance 357
#define TalentClassifiedFireCrestExplosionDamage 358
#define TalentClassifiedFireCrestExplosionRadius 359
#define TalentClassifiedFireCrestExplosionCooldown 360
#define TalentClassifiedBanshee 361
#define TalentClassifiedBansheeBonusDamagePerManhuntStage 362
#define TalentClassifiedBansheeInteractDurationBonus 363
#define TalentClassifiedBansheeInteractDurationRange 364
#define TalentClassifiedSolo 365
#define TalentClassifiedSoloRotationDuration 366
#define TalentClassifiedSoloSkillDuration 367
#define TalentClassifiedSoloAttributeRelationPercentage 368
#define TalentClassifiedSoloAttributeRelationPenalty 369
#define TalentClassifiedSoloMinAttributeRelationModifier 370
#define PrimaryDefensive 371
#define PrimaryOffensive 372
#define PrimarySupport 373
#define OverHeal 374
#define OverHealDepletionDelay 375
#define OverHealDepletionRate 376
#define SignatureSkillResourceRewardMod 377
#define CombatBuff_Cooldown_ 378
#define DefenceBuff_Cooldown_ 379
#define GroupHeal_Cooldown_ 380
#define ModSocketAttributeBonus 381
#define ArmorMitigationDefaultRatingFlatBonus 382
#define ContaminationZoneGasMaskLevelDefaultFlatBonus 383
#define DefaultInventoryFlatBonus 384
#define WeaponDamageBaseModBonus 385
#define WeaponDamageAssaultRifleBaseModBonus 386
#define WeaponDamageLMGBaseModBonus 387
#define WeaponDamageMarksmanRifleBaseModBonus 388
#define WeaponDamagePistolBaseModBonus 389
#define WeaponDamageShotgunBaseModBonus 390
#define WeaponDamageSMGBaseModBonus 391
#define PrimaryOffensiveFlatBonus 392
#define PrimaryDefensiveFlatBonus 393
#define PrimarySupportFlatBonus 394
#define PrimaryDefensiveDefaultBaseFlatBonus 395
#define PrimaryOffensiveDefaultBaseFlatBonus 396
#define PrimarySupportDefaultBaseFlatBonus 397
#define PrimaryDefensiveDefaultFlatBonus 398
#define PrimaryOffensiveDefaultFlatBonus 399
#define PrimarySupportDefaultFlatBonus 400
#define PrimaryOffensiveClassifiedFlatBonus 401
#define PrimaryDefensiveClassifiedFlatBonus 402
#define PrimarySupportClassifiedFlatBonus 403
#define PrimaryDefensiveClassifiedDefaultBaseFlatBonus 404
#define PrimaryOffensiveClassifiedDefaultBaseFlatBonus 405
#define PrimarySupportClassifiedDefaultBaseFlatBonus 406
#define AmmoIncendiary 407
#define AmmoIncendiaryFlatBonus 408
#define AmmoExplosive 409
#define ApplyStatusBurnPercentage 410
#define ApplyExplosionConsumablePercentage 411
#define ArmorRatingUI 412
#define ToughnessUI 413
#define DefaultInventoryUI 414
#define ContaminationProtectionUI 415
#define SkillPowerUI 416
#define WeaponDamageCompareUI 417
#define WeaponRPMCompareUI 418
#define WeaponMagazineCompareUI 419
#define WeaponAccuracyCompareUI 420
#define WeaponRangeCompareUI 421
#define WeaponReloadTimeCompareUI 422
#define WeaponStabilityCompareUI 423
#define MedkitStack 424
#define SMGAmmo 425
#define ShotgunAmmo 426
#define MarksmanRifleAmmo 427
#define LMGAmmo 428
#define AssaultRifleAmmo 429
#define Survival_TemperatureRating 430
#define Survival_Cold 431
#define Survival_Disease 432
#define Survival_Hunger 433
#define Survival_Thirst 434
#define Survival_ColdAimShakeSpeed 435
#define Survival_UIDistanceMultiplier 436
#define Survival_ConsumableFoodCooldown 437
#define Survival_ConsumableDrinkCooldown 438
#define Survival_ConsumableMedicineCooldown 439
#define Survival_ConsumableMedicineDiminishingReturn 440
#define Survival_ConsumableMedicineDurationMaxTime 441
#define Survival_ConsumableMedicineCooldownMaxTime 442
#define Survival_ConsumablePainkillerCooldown 443
#define Survival_ConsumablePainkillerDiminishingReturn 444
#define Survival_ConsumablePainkillerDurationMaxTime 445
#define Survival_ConsumablePainkillerCooldownMaxTime 446
#define PvPDamageMultiplierArms 447
#define PvPDamageMultiplierBody 448
#define PvPDamageMultiplierHead 449
#define PvPDamageMultiplierLegs 450
#define GrenadeEMPStack 451
#define GrenadeFlashbangStack 452
#define GrenadeHEStack 453
#define GrenadeIncendiaryStack 454
#define GrenadeShockStack 455
#define GrenadeTearGasStack 456
#define NormalizedWeaponDamageModBonus 457
#define Seasons_RottenToTheCore_GlobalModifiers_BleedRadius 458
#define Seasons_RottenToTheCore_GlobalModifiers_HeadshotBonusTimer 459
#define Seasons_RottenToTheCore_GlobalModifiers_HeadshotBonusCritDamage 460
#define Seasons_RottenToTheCore_GlobalModifiers_CurrentHeadShotDamageBonus 461
#define Seasons_DangerZone_GlobalModifiers_PlayerInflictEnemyDamageExtraMultiplier 462
#define Seasons_DangerZone_GlobalModifiers_PlayerInflictEnemyDamageRadius 463
#define Seasons_DangerZone_ActivityModifiers_EnemyInflictPlayerDamageExtraMultiplier 464
#define Seasons_DangerZone_ActivityModifiers_EnemyInflictPlayerDamageRadius 465
#define Seasons_DangerZone_GroupModifiers_PlayerInflictEnemyDamageNearAllyExtraMultiplier 466
#define Seasons_DangerZone_GroupModifiers_PlayerInflictEnemyDamageNearAllyRadius 467
#define Seasons_DangerZone_GroupModifiers_EnemyInflictPlayerDamageFarAllyExtraMultiplier 468
#define Seasons_DangerZone_GroupModifiers_EnemyInflictPlayerDamageFarAllyRadius 469
#define Seasons_HandleWithCare_Active 470
#define Seasons_StayPut_GlobalModifiers_MaxBonusDamage 471
#define Seasons_StayPut_GlobalModifiers_BuildUpSpeedWhileNotMoving 472
#define Seasons_StayPut_GlobalModifiers_DepletionSpeedWhileMoving 473
#define Seasons_StayPut_GlobalModifiers_RevivedGracePeriodDuration 474
#define Seasons_StayPut_GroupModifiers_NearAllyRadius 475
#define Seasons_StayPut_GroupModifiers_NearAllyDepletionSpeed 476
#define Seasons_StayPut_GroupModifiers_TeamKillsRequiredAmount 477
#define Seasons_StayPut_GroupModifiers_TeamKillsWindowTimer 478
#define Seasons_StayPut_GroupModifiers_TeamKillsRewardDuration 479
#define Seasons_HandleWithCare_GlobalModifier_UI_ExplosionTimer 480
#define Seasons_PrototypeBullets_Active 481
#define Seasons_PrototypeBullets_MatchedWeaknessMaxHealthPercentageDamage 482
#define Seasons_PrototypeBullets_MatchedWeaknessDamageTakenModBonus 483
#define Seasons_PrototypeBullets_MatchedWeaknessDamageTakenModBonusDuration 484
#define Seasons_PrototypeBullets_GasBulletsAOE 485
#define Seasons_PrototypeBullets_MagicBulletsCooldownTime 486
#define Seasons_Shocker_Active 487
#define AtributeIndexMax 488

typedef struct KeyName
{
	const char * key;
	int vk;
} KeyName;

static KeyName CONFIG_KEYS[] = {
	{ "0" , 0x30 },
	{ "1" , 0x31 },
	{ "2" , 0x32 },
	{ "3" , 0x33 },
	{ "4" , 0x34 },
	{ "5" , 0x35 },
	{ "6" , 0x36 },
	{ "7" , 0x37 },
	{ "8" , 0x38 },
	{ "9" , 0x39 },
	{ "a" , 0x41 },
	{ "b" , 0x42 },
	{ "c" , 0x43 },
	{ "d" , 0x44 },
	{ "e" , 0x45 },
	{ "f" , 0x46 },
	{ "g" , 0x47 },
	{ "h" , 0x48 },
	{ "i" , 0x49 },
	{ "j" , 0x4A },
	{ "k" , 0x4B },
	{ "l" , 0x4C },
	{ "m" , 0x4D },
	{ "n" , 0x4E },
	{ "o" , 0x4F },
	{ "p" , 0x50 },
	{ "q" , 0x51 },
	{ "r" , 0x52 },
	{ "s" , 0x53 },
	{ "t" , 0x54 },
	{ "u" , 0x55 },
	{ "v" , 0x56 },
	{ "w" , 0x57 },
	{ "x" , 0x58 },
	{ "y" , 0x59 },
	{ "Z",  0x5A },
	{ "ADD",        VK_ADD },
	{ "BACKSLASH",	VK_SEPARATOR },
	{ "BACKSPACE",	VK_BACK },
	{ "CAPITAL",	VK_CAPITAL },
	{ "CAPS",		VK_CAPITAL },
	{ "CAPSLOCK",	VK_CAPITAL },
	{ "CLEAR",		VK_CLEAR },
	{ "COMMA",		VK_OEM_COMMA },
	{ "DECIMAL",	VK_DECIMAL },
	{ "DELETE",		VK_DELETE },
	{ "DIVIDE",		VK_DIVIDE },
	{ "DOWN",		VK_DOWN },
	{ "END",		VK_END },
	{ "ESC",		VK_ESCAPE },
	{ "ESCAPE",		VK_ESCAPE },
	{ "F1",			VK_F1 },
	{ "F10",		VK_F10 },
	{ "F11",		VK_F11 },
	{ "F12",		VK_F12 },
	{ "F2",			VK_F2 },
	{ "F3",			VK_F3 },
	{ "F4",			VK_F4 },
	{ "F5",			VK_F5 },
	{ "F6",			VK_F6 },
	{ "F7",			VK_F7 },
	{ "F8",			VK_F8 },
	{ "F9",			VK_F9 },
	{ "HOME",		VK_HOME },
	{ "INSERT",		VK_INSERT },
	{ "LBUTTON",	VK_LBUTTON },
	{ "LEFT",		VK_LEFT },
	{ "MBUTTON",	VK_MBUTTON },
	{ "MULTIPLY",	VK_MULTIPLY },
	{ "MINUS",		VK_OEM_MINUS },
	{ "NUM0",		VK_NUMPAD0 },
	{ "NUM1",		VK_NUMPAD1 },
	{ "NUM2",		VK_NUMPAD2 },
	{ "NUM3",		VK_NUMPAD3 },
	{ "NUM4",		VK_NUMPAD4 },
	{ "NUM5",		VK_NUMPAD5 },
	{ "NUM6",		VK_NUMPAD6 },
	{ "NUM7",		VK_NUMPAD7 },
	{ "NUM8",		VK_NUMPAD8 },
	{ "NUM9",		VK_NUMPAD9 },
	{ "NUMLOCK",	VK_NUMLOCK },
	{ "OEM1",		VK_OEM_1 },
	{ "OEM2",		VK_OEM_2 },
	{ "OEM3",		VK_OEM_3 },
	{ "OEM4",		VK_OEM_4 },
	{ "OEM5",		VK_OEM_5 },
	{ "OEM6",		VK_OEM_6 },
	{ "OEM7",		VK_OEM_7 },
	{ "OEM8",		VK_OEM_8 },
	{ "PAGEDOWN",	VK_NEXT },
	{ "PAGEUP",		VK_PRIOR },
	{ "PAUSE",		VK_PAUSE },
	{ "PERIOD",		VK_OEM_PERIOD },
	{ "PLUS",		VK_OEM_PLUS },
	{ "PRINT",		VK_PRINT },
	{ "RBUTTON",	VK_RBUTTON },
	{ "RETURN",		VK_RETURN },
	{ "RIGHT",		VK_RIGHT },
	{ "SCROLL",		VK_SCROLL },
	{ "SELECT",		VK_SELECT },
	{ "SEPARATOR",	VK_SEPARATOR },
	{ "SPACE",		VK_SPACE },
	{ "SUBTRACT",	VK_SUBTRACT },
	{ "TAB",		VK_TAB },
	{ "UP",			VK_UP },
	{ "XBUTTON1",	VK_XBUTTON1 },
	{ "XBUTTON2",	VK_XBUTTON2 },
};





