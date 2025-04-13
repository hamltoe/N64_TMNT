#include <cstdint> // Required for uint8_t and uint16_t

// Compact 16-bit entity ID (8-bit ID + 8-bit instance)
typedef union {
    struct {
        uint8_t instanceIndex;
        uint8_t ID;
    };
    uint16_t entityID;
} EntityID;

enum CharacterType { // Types of characters in the game
    Player, // This is controlled by the player; the rest are AI-controlled.
    Neuteral,
    Hostile,
    Friendly,
    Enemy,
    Ally,
    Boss = 6 // 666 Mark of the beast
};

enum CharacterState {
    // Core Movement States
    Idle = 0,           // Standing still
    Walking,            // Basic forward/backward movement
    Running,            // Faster movement
    Jumping,            // Character jumps up
    Falling,            // Character falling after jump
    Climbing,           // Climbing ladders, ropes, etc.
    Dying,              // Character death animation
    Stunned,            // Temporarily immobile after hit

    // Basic Combat States
    Attacking,          // Basic attack (single strike)
    // ...additional states...
};

// Compact 16-bit entity ID (8-bit type + 8-bit instance)
typedef union {
    struct {
        uint8_t instanceIndex;
        uint8_t characterType;
    };
    uint16_t entityID;
} EntityID;

struct Character{
    /* Simple entity with ID and list of components */
    int id; // ID of the character
    
    CharacterType type; // Type of character (e.g., hero, villain, etc.)
    int components[]; // Array of components attached to the character

};

enum CharacterType { // Types of characters in the game
    Player,//This is controlled by the player the rest are Ai controlled.
    Neuteral,
    Hostile,
    Friendly,
    Enemy,
    Ally,
    Boss = 6 //666 Mark of the beast
};

enum CharacterState
{
    // Core Movement States
    Idle = 0,           // Standing still
    Walking,            // Basic forward/backward movement
    Running,            // Faster movement
    Jumping,            // Character jumps up
    Falling,            // Character falling after jump
    Climbing,           // Climbing ladders, ropes, etc.
    Dying,              // Character death animation
    Stunned,            // Temporarily immobile after hit

    // Basic Combat States
    Attacking,          // Basic attack (single strike)
    Defending,          // Blocking/parrying attacks
    Dodging,            // Quick step or roll to avoid damage
    Grabbing,           // Initiating a grapple or grab
    Thrown,             // Being thrown by an opponent
    Countering,         // Deflecting an enemy attack
    Blocking,           // Deflecting/blocking projectiles
    Recoiling,          // Taking knockback after hit

    // Advanced Combat and Combo States
    ComboStarter,       // Initial attack that triggers combo
    ComboMid,           // Mid-combo follow-up attack
    ComboFinisher,      // Final combo strike
    AerialCombo,        // Combo string executed mid-air
    GroundSlam,         // Slamming enemy into ground
    AirLauncher,        // Launches enemy into the air
    AirJuggle,          // Keeping enemy airborne with strikes
    PowerAttack,        // Stronger charged attack
    SpecialAttack,      // Signature move unique to each character
    UltimateMove,       // High-damage finisher move
    GrabThrow,          // Grapple move that throws enemy
    GrabPummel,         // Grapple with repeated punches/kicks
    GrabFinisher,       // Ends grapple with finisher move

    // Weapon-Based Attacks
    WeaponSwing,        // Basic weapon strike
    WeaponCombo,        // Series of weapon strikes
    WeaponCharge,       // Charged attack with weapon
    WeaponSpecial,      // Special weapon move
    ThrowWeapon,        // Projectile attack with throwable weapon
    WeaponParry,        // Counter with weapon deflection
    WeaponGroundSlam,   // Slam weapon to cause area damage

    // Ranged/Projectile Attacks
    ThrowingStar,       // Shuriken throw
    KunaiThrow,         // Throwable Foot Soldier weapon
    GrapplingHook,      // Pull enemy or interact with environment
    LaserShot,          // Ranged laser blast
    ExplosiveThrow,     // Toss grenade or explosive
    Fireball,           // Projectile dealing flame damage

    // Mobility & Evasive Maneuvers
    WallJump,           // Jumping off walls to reposition
    Roll,               // Rolling to evade attacks
    Dash,               // Quick burst of speed
    SlideKick,          // Low evasive attack
    Backflip,           // Backward aerial dodge
    AerialDodge,        // Mid-air evasion
    WallClimb,          // Vertical movement on walls
    WallHang,           // Temporary cling to wall before jump
    LedgeGrab,          // Grab onto ledges when falling
    AirRecovery,        // Quick mid-air recovery after hit

    // Defensive & Counter Techniques
    PerfectBlock,       // Block timed perfectly to negate damage
    Reflect,            // Reflect incoming projectile
    Parry,              // Deflect melee attacks with perfect timing
    CounterAttack,      // Instant follow-up strike after parry
    AutoDodge,          // Evasive maneuver triggered on perfect timing
    EnergyShield,       // Creates temporary shield
    DefensiveRoll,      // Quick evasive roll after blocking
    DamageResist,       // Temporary resistance to incoming damage

    // Contextual & Environmental Interactions
    Interacting,        // Using objects in the environment
    PickingUp,          // Picking up weapons or items
    ThrowingObject,     // Throwing environmental objects
    Swinging,           // Using ropes, poles, or pipes to swing
    ClimbingLedge,      // Grabbing and pulling up onto ledge
    PushingObject,      // Pushing objects to reposition them
    PullingLever,       // Interacting with levers and switches
    RidingVehicle,      // Controlling vehicles like Turtle Van
    Balancing,          // Maintaining balance on moving surfaces
    UsingGadget,        // Using items like T-Communicator or ShellCell

    // Team and Multiplayer Interactions
    RevivingAlly,       // Helping fallen ally recover
    Assisting,          // Providing support or combo assist
    TeamCombo,          // Coordinated combo with ally
    TurtleFormation,    // Unique formation-based attack
    BuffingAlly,        // Temporarily boosting ally’s stats
    TeamBlock,          // Blocking attacks for an ally
    CombinedUltimate,   // High-damage ultimate combo

    // Aerial & High-Risk Moves
    DiveKick,           // Aerial dive attack
    AirSlam,            // Grabbing enemy in air and slamming down
    DoubleJump,         // Additional jump mid-air
    AirDash,            // Quick aerial burst to evade
    MidAirGrab,         // Grabbing enemy mid-air
    Hovering,           // Temporary air stall

    // Special & Power-Up States
    MutagenBoost,       // Temporarily enhanced attack and speed
    TurtlePowerMode,    // Grants invincibility and boosted damage
    HyperFocus,         // Slows time briefly for perfect execution
    RageMode,           // Increases speed and damage after taking damage
    NinjaReflex,        // Heightened agility and evasion
    PowerSurge,         // Unleashes powerful shockwave on activation
    TimeStop,           // Temporarily freezes enemies
    DimensionWarp,      // Teleports to another area

    // Hazard & Status Effects
    Burning,            // Taking damage over time from fire
    Frozen,             // Immobilized due to ice attacks
    Poisoned,           // Gradual health drain
    Electrified,        // Stunned by electric damage
    Confused,           // Movement and controls reversed
    Slowed,             // Movement and attack speed reduced
    Silenced,           // Prevented from using abilities

    // Additional Contextual States
    Taunting,           // Taunting to enrage enemies
    Celebrating,        // Post-victory celebration
    Sleeping,           // Immobilized temporarily (non-combat)
    Possessed,          // Temporary mind control by enemies
    Transforming,       // Transitioning to powered-up form
    Summoning,          // Calling allies or NPCs for aid
    ShieldingAlly,      // Protecting an ally from attacks
    Retreating,         // Moving away strategically
    TacticalStance,     // Preparing for specific combo or counter

    // Unique TMNT-Themed Special Moves
    ShellSpin,          // Defensive spinning shell attack
    SewerSlide,         // Low sliding attack
    BoomerangPizza,     // Pizza box projectile that returns
    ShellBounce,        // Bounces on enemies to deal damage
    TurtleTornado,      // Aerial spin attack, hitting multiple foes
    SewerDive,          // Dive into sewer to evade and reposition
    PowerShell,         // Charged spinning shell for knockback
    KatanaWhirlwind,    // Leonardo’s rapid strike combo
    NunchakuFury,       // Michelangelo’s rapid nunchaku attacks
    BoStaffCyclone,     // Donatello’s wide area sweep
    SaiStrike,          // Raphael’s devastating sai combo
};


enum EntitySpawnList { // The first 127 are characters, the other 128 are items.
    
    LastEntity = 0,    // Special Command to spawn the last type of item  as the previous call

    // Characters      
    Leonardo = 1,      // Blue, leader, katana swords
    Michelangelo = 2,  // Orange, nunchaku, comic relief
    Donatello = 3,     // Purple, bo staff, tech genius
    Raphael = 4,       // Red, sai, hot-headed
    Splinter,          // Sensei, mutant rat
    AprilONeil,        // Channel 6 news reporter
    CaseyJones,        // Vigilante, hockey mask
    Shredder,          // Oroku Saki, main villain
    Krang,             // Brain-like warlord from Dimension X
    Bebop,             // Mutant warthog, Shredder’s henchman
    Rocksteady,        // Mutant rhinoceros, Shredder’s henchman
    BaxterStockman,    // Scientist turned mutant fly
    RatKing,           // Sewer dweller with control over rats
    Karai,             // Female ninja, Foot Clan leader in 1990s comics
    Tatsu,             // Shredder’s right-hand man (live-action movies)

    // Foot Clan Variations
    FootSoldier,       // Standard Foot Soldier (Purple)
    EliteFoot,         // Elite Foot Soldiers with naginata
    FootCommander,     // Leader of elite Foot Soldiers
    RoboticFoot,       // Robotic Foot Soldiers (arcade version)
    FootJuggernaut,    // Heavy Foot enforcer
    FootAssassin,      // Stealth-based elite Foot killer
    FootDrone,         // Flying Foot surveillance units
    FootTactician,     // Strategic Foot unit with advanced AI
    FootFlame,         // Foot Soldier armed with flamethrower
    FootSniper,        // Foot Soldier with projectile attacks

    // Major Villains and Bosses
    Metalhead,         // Robot turtle, Donatello’s creation
    Tokka,             // Mutant snapping turtle (Secret of the Ooze)
    Rahzar,            // Mutant wolf (Secret of the Ooze)
    Leatherhead,       // Mutant alligator, Cajun adversary
    Slash,             // Evil mutant turtle, arcade boss
    BaxterFly,         // Mutant fly version of Baxter Stockman
    ChromeDome,        // Giant robot Foot leader
    Dirtbag,           // Mutant mole, arcade mini-boss
    Groundchuck,       // Mutant bull with cyber enhancements
    Triceraton,        // Alien dinosaur warriors from Dimension X
    PizzaMonster,      // Alien pizza monster enemies (cartoon/arcade)
    Tempestra,         // Virtual reality villain from the cartoon
    RatKingArcade,     // Arcade version of Rat King
    Scumbug,           // Mutant cockroach from 1987 series
    Wyrm,              // Mutant worm, 1990s comics and toyline
    Armaggon,          // Mutant shark from 1990s Archie Comics
    Antrax,            // Mutant ant, Foot Clan enforcer
    SuperShredder,     // Final form of Shredder in Secret of the Ooze

    // Krang Variations
    KrangSmall,        // Original smaller version of Krang from the 1987 cartoon
    KrangWalker,       // Krang in walker suit (arcade boss)
    KrangRobot,        // Krang’s robot body (1987 series)

    // Extended Villains and Enforcers
    BaxterStockmanHuman, // Human version of Baxter Stockman
    MechaTurtle,       // Evil cyber turtle clone (arcade boss)
    CyberShredder,     // Digital version of Shredder (arcade)
    ShadowShredder,    // Dark clone of Shredder (arcade sequel)
    TokkaArcade,       // Video game version of Tokka (Turtles in Time)
    RahzarArcade,      // Video game version of Rahzar (Turtles in Time)
    DimensionXGuard,   // Krang’s elite guards from Dimension X
    MutagenMan,        // Mutated human with transparent body
    LordDregg,         // Alien conqueror from later 1987 seasons
    Sarnath,           // Alien scientist from Dimension X
    SavantiRomero,     // Time-traveling sorcerer from 1990s comics

    // Supporting Allies
    MonaLisa,          // Mutant lizard, ally to the turtles
    MondoGecko,        // Skateboarding mutant gecko
    Fugitoid,          // Professor Honeycutt, robot ally
    LotusBlossom,      // Female ninja with honor code
    GenghisFrog,       // Mutant frog, leader of the Punk Frogs
    NapoleonBonafrog,  // Mutant frog with attitude
    AttilaTheFrog,     // Mutant frog ally
    RasputinTheMadFrog,// Mutant frog, weapon specialist
    Carter,            // Human ally from 1987 series later seasons
    Renet,             // Time-traveling ally from 1990s comics

    // Arcade/Video Game Hazards/Enemies
    Mouser,            // Small robotic enemies created by Baxter
    RoadkillRodney,    // Robot enemies from arcade games
    StoneWarrior,      // Rock soldiers from Dimension X
    MutantAlligator,   // Sewer hazard enemy
    ElectricEel,       // Sewer enemy, electric hazard
    SewerGator,        // Swamp creature, arcade hazard
    Bludgeon,          // Mutant hammerhead shark (toyline)

    // Mutants and Mutated Villains
    KingKomodo,        // Mutant komodo dragon from comics
    ArmoredDon,        // Armored version of Donatello (toyline)
    TurtleBot,         // Evil robot turtle from arcade games
    Primeape,          // Gorilla mutant from 1990s toyline
    BigMacca,          // Mutant gorilla, arcade exclusive
    Krush,             // Mutant crocodile (toyline)
    Mogul,             // Mystical Foot Clan entity from comics
    DimensionXHunter,  // Alien bounty hunter from 1990s comics

    // Foot Elite and Clones
    CyberRatKing,      // Digital version of Rat King (arcade)
    ChronoFoot,        // Time-traveling Foot enforcer
    DarkTurtle,        // Evil clone of Leonardo (cartoon)
    MechaSplinter,     // Evil robot clone of Splinter
    FootEliteCommander,// High-ranking Foot leader
    FootSaboteurElite, // Elite version of explosive specialist
    FootSniperElite,   // Advanced sniper Foot unit (toyline)

    // Mutant Variations and Advanced Enemies
    RaptorX,           // Mutant dinosaur ally (comics)
    FootMecha,         // Foot Soldier with cyber enhancements
    FootKnight,        // Foot Clan knight with medieval weapons
    FootFlameElite,    // Elite Foot Soldier with flamethrower
    EliteMutant,       // Advanced mutant variant from comics
    FootCommander2,    // Enhanced Foot leader (toyline)
    GhostFoot,         // Foot Soldier with stealth abilities

    // Extended Heroes and Background Characters
    Nightwatcher,      // Casey Jones’ alter ego (live-action)
    TangShen,          // Splinter’s love interest (comics)
    KingLionheart,     // Mutant lion, 1990s toyline
    Headdrop,          // Mutant sumo wrestler from comics
    Silver,            // Mutant gorilla from 1990s Archie Comics
    GhostBear,         // Wrestling champion from 1990s series
    AgentBishop,       // Government agent (1990s adaptation)

    // Final Bosses and Advanced Forms
    UltimateShredder,  // Shredder’s ultimate mutation
    Mechaturtle,       // Cybernetic evil turtle (arcade boss)
    MutantWarrior,     // Final mutant warrior boss
    UltimateFoot,      // Final boss form of Foot Clan elite
    TurtlePrime,       // Superior version of Leonardo (toyline)
    FootKnightElite,   // Enhanced Foot knight with more armor
    DimensionXWarden,  // Warden from Dimension X (comics)
    FootSaboteur2,     // Advanced saboteur Foot unit (arcade)
    MutantMaster,      // Overlord of Foot Mutants (toyline)
    ChronoKnight,      // Time-traveling Foot enforcer
    FootDroneElite,    // Upgraded Foot surveillance unit
    MechaFoot,         // Advanced cybernetic Foot clone
    ShadowShredder2,   // Final form of Shredder’s dark clone
    UltimateShredder2, // Enhanced Shredder’s final form
    EliteCommander,    // Foot leader with advanced AI
    KrangWalkerPrime,  // Final form of Krang’s walker
    FootWarlord,       // Ultimate Foot Clan commander
    FootAssassin2,     // Upgraded stealth killer Foot variant
    UltimateFoot2,     // Final elite form of Foot Clan bosses
    SplinterClone,     // Mutant clone of Splinter
    DarkFoot,          // Shadowy Foot variant
    UltimateMutagenMan,// Enhanced version of Mutagen Man
    DimensionXBoss,     // Final boss from Dimension X
    
    //End of character list and start items list
    
    // Weapon Pickups
    Katana,             // Leonardo’s weapon
    Nunchaku,           // Michelangelo’s weapon
    BoStaff,            // Donatello’s weapon
    Sai,                // Raphael’s weapon
    ThrowingStar,       // Shuriken projectile
    SmokeBomb,          // Temporary invisibility
    ElectricNunchaku,   // Enhanced version of Michelangelo’s weapon
    FlameKatana,        // Fire-imbued version of Leonardo’s katana
    IceSai,             // Ice-powered sai
    PlasmaBoStaff,      // Enhanced Donatello’s bo with plasma
    GrapplingHook,      // Secondary weapon, used for traversal
    Kunai,              // Throwable Foot Soldier weapon
    LaserGun,           // Dimension X Foot Soldier weapon
    MouserControlStick, // Used to control Mousers
    ExplodingKunai,     // Throwable explosive variant

    // Power-Ups & Buffs
    Pizza,              // Restores health
    SuperPizza,         // Full health restore
    EnergyDrink,        // Temporary speed boost
    TurtlePower,        // Invincibility for a short period
    PowerCrystal,       // Temporarily doubles attack damage
    Mutagen,            // Randomly mutates player with buffs/debuffs
    RadarBooster,       // Reveals enemy locations temporarily
    CloakingDevice,     // Temporary invisibility
    TimeStopper,        // Freezes all enemies temporarily
    DimensionKey,       // Opens portals to Dimension X
    EnergyAmplifier,    // Increases attack range temporarily

    // Throwable Items / Explosives
    TrashCanLid,        // Throwable, low damage
    SewerLid,           // Heavy throwable, high damage
    FireExtinguisher,   // Can knock back enemies with foam blast
    Barrel,             // Throwable, high impact
    TNTBarrel,          // Explosive variant, area damage
    Grenade,            // Throwable, high explosion radius
    Dynamite,           // Large explosion, delayed fuse
    OilDrum,            // Ignites for flame trap
    ChemicalCanister,   // Releases gas to stun enemies
    Crate,              // Throwable crate, breakable
    ExplodingPizzaBox,  // Joke item, explodes on impact

    // Interactables / Environmental Objects
    ArcadeMachine,      // Can be destroyed for points or loot
    FireHydrant,        // Can be struck to release water
    StreetLamp,         // Can be knocked down for damage
    ManholeCover,       // Flips up to hit enemies
    Payphone,           // Breaks for extra points or items
    CarHood,            // Can be used as cover or throwable
    GarbageCan,         // Breakable object, may contain items
    VendingMachine,     // Breakable, can drop food or power-ups
    PizzaSign,          // Can be used as projectile
    TVMonitor,          // Electric hazard, stuns enemies
    ChemicalBarrel,     // Can cause explosion or status effect
    HangingLight,       // Can be knocked down to damage enemies
    FootSoldierTrap,    // Hidden device triggered by enemies

    // Doors and Traps
    SewerGrate,         // Opens to drop enemies into the sewer
    SlidingMetalDoor,   // Opens with keycard or after defeating enemies
    TrapDoor,           // Drops into hazard below
    WarehouseDoor,      // Opens after solving puzzle or defeating bosses
    DimensionXPortal,   // Opens to teleport players or enemies
    ElectrifiedGate,    // Hazard, damages players/enemies on contact
    LaserBarrier,       // Needs to be deactivated to pass
    BoobyTrappedWall,   // Wall explodes if touched
    SecurityGate,       // Locked until Foot Soldiers are defeated
    LockedManhole,      // Opens after finding key

    // Keys and Unlockables
    SewerKey,           // Unlocks sewer doors
    FootKeycard,        // Opens Foot Soldier-controlled gates
    WarehousePass,      // Allows entry to restricted areas
    DimensionXKey,      // Unlocks portals to Dimension X
    TurtleLairPass,     // Grants access to safe zone
    EmergencyOverride,  // Deactivates traps and security systems
    HackingDevice,      // Used to unlock electronic doors

    // Gadgets and Tools
    TCommunicator,     // Allows communication between turtles
    TurtleVanRemote,    // Summons the Turtle Van for backup
    ShellCell,          // Portable communication device
    SewerScanner,       // Detects hidden paths and items
    TechPack,           // Used to fix broken tech or hack systems
    DimensionTracker,   // Used to detect Dimension X portals
    PortalInhibitor,    // Stops enemies from teleporting in
    CloakingField,      // Stealth mode for short time
    WristBlaster,       // Small arm cannon, medium damage
    FootJammer,         // Disables Foot Soldier communications
    SensorBomb,         // Detects and detonates on proximity
    VRTrainingDisc,     // Unlocks new moves and combos
    SurveillanceDrone,  // Can scout ahead in stealth areas

    // Widgets & HUD Elements
    MiniMap,            // Displays map with enemy locations
    RadarScanner,       // Reveals hidden enemies or traps
    PowerMeter,         // Tracks special move energy
    TurtleTracker,      // Shows status of teammates
    ComboCounter,       // Displays combo progress
    ObjectiveMarker,    // Highlights mission objectives
    HealthBar,          // Displays player/enemy health
    TimeCounter,        // Counts down mission or level time
    AlertIndicator,     // Warns of incoming danger or traps
    PortalWarning,      // Indicates Dimension X activity

    // Vehicles and Rideables
    TurtleVan,          // Iconic vehicle, provides backup
    ShellCycle,         // Motorcycle for quick traversal
    FootSkiff,          // Foot Soldier transport, can be hijacked
    SewerBoard,         // Sewer surfing rideable, speed boost
    HoverDrone,         // Small rideable for mid-air traversal
    BattleShell,        // Armored vehicle with weaponry
    TurtleBlimp,        // Airship, used to navigate higher areas

    // Power-Up Variations / Special Items
    SuperBomb,          // Clears entire screen of enemies
    ExtraLife,          // Grants 1 additional life
    ScoreMultiplier,    // Temporarily doubles points earned
    InstantCombo,       // Instantly fills combo meter
    ShieldBooster,      // Increases defense temporarily
    PizzaSlice,         // Partial health restore
    FullPizza,          // Full health restore for all players
    RagePower,          // Boosts attack and speed
    NinjaSpirit,        // Summons an AI ally to assist
    HyperMode,          // Maxes out speed and attack briefly
    DimensionWarp,      // Instantly transports player to safe zone

    // Special Traps & Hazards
    LaserTurret,        // Automatic turret firing at players
    FloorSpikes,        // Pops up when triggered
    FlameThrowerTrap,   // Shoots fire across the floor
    FallingRocks,       // Drops hazards from above
    ElectricGrid,       // Stuns players/enemies on contact
    MovingPlatforms,    // Forces players to maintain balance
    OilSlick,           // Causes slip, loss of control
    ConveyorBelt,       // Pushes players toward hazards
    GravityField,       // Pulls enemies or players toward center
    ShockTrap,          // Electrifies environment momentarily
    AcidPit,            // Damage over time if fallen into

    // Miscellaneous/Bonus Items
    TurtlePlush,        // Bonus points or secret item
    VHSCassette,        // Easter egg referencing old cartoon
    FootClanSymbol,     // Collectible to unlock extras
    ArcadeToken,        // Secret item that references original arcade game
    NinjaMedal,         // Earned by performing flawless combos
    DimensionMap,       // Reveals hidden locations
    PizzaBox,           // Extra points or hidden power-up
    RareComic,          // Unlocks alternate costumes
    ShellFragment,      // Collect to unlock secret content
    FootClanManual      // Unlocks strategy hints or secrets
};

