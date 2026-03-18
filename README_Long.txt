================================================================================
  HOOK & SWIM
  Theme: Transform
================================================================================

  A tiny two-mode arcade/adventure where you swap between Human and Fish
  forms -> fish for treasure, sell to grow your economy, and survive
  the sea to become rich.


================================================================================
  HOW TO PLAY
================================================================================

  Controls
  --------
  WASD        Move (Human and Fish)
  SHIFT       Sprint (hold) / sprint sideways
  F           Interact with:
                - Shops (Seller, Upgrades, DebtHolder)
                - Fishing zones
                - Chests (collect)
  SPACE       Start game (home screen)
  P           Pause (return to home)
  ESC         Quit
  CTRL + T    Reset save (wipe saved progression)


================================================================================
  2 MODES
================================================================================

  - Human mode
  - Fish mode

  Objective
  ---------
  - Earn coins
  - Improve your economy (upgrades, multipliers)
  - Avoid losses (enemies steal money)
  - Repay your debt to the Church -- reach 1,000,000,000 coins to win

  How to earn money
  -----------------
  - Catch chests in the sea (treasure)
  - Fish at the pier/mole (timing mini-game)

  How to use money
  ----------------
  - Improve economy (income multiplier)
  - Enhance fish skills (stamina, inventory upgrades)
  - Repay your debt at the DebtHolder


================================================================================
  GAME MAIN MECHANICS
================================================================================

  Human mode
  ----------
  - Top-down view & movement
  - Free exploration around town and pier
  - Fishing mini-game when on the mole:
      timing based -> get closer to center to increase rarity
      fish have four rarities: Common, Rare, Epic, Legendary
  - Sell fish and chests to the Seller to collect coins
  - Buy upgrades (stamina, multiplier, inventory size)
  - Pay the DebtHolder to progress toward freedom
  - Stamina system:
      sprinting drains stamina; recovers when not sprinting

  Fish mode
  ---------
  - 2D platformer view & movement
  - Enemies (shark-like fishes) that steal coins if they catch you
  - Treasures / Chests:
      chests contain a coin value and move with Perlin Noise
      limited number of chests per session
  - Stamina system:
      sprinting drains stamina; recovers when not sprinting

  Losses / Penalties
  ------------------
  This game is idle-ish -- you don't "die" permanently, but there are penalties:

  - Enemies can steal coins (avoid being caught)
  - If coins drop below zero you lose all chests in your inventory


================================================================================
  STORY
================================================================================

  For years, you lived a modest life in a small coastal town -- unnoticed,
  unremarkable, and comfortably invisible to the world.
  Until the day the Church came for you.

  No one truly remembers how the debt began. Some say it was a failed
  investment blessed by the wrong priest. Others whisper about a contract
  you signed without reading the fine print.
  What matters is this:

      YOU OWE THE CHURCH ONE BILLION COINS.

  Unable to pay, you were exiled to a remote archipelago at the edge of
  civilization -- a place reserved for debtors with only one path left to
  redemption: repay what you owe, no matter how long it takes.

      Escape is impossible. Forgiveness is not negotiable.

  But fate has given you something unusual.
  After a shipwreck that should have claimed your life, you awoke with a
  mysterious ability -- the power to shift between human and fish. A
  miracle... or perhaps part of your punishment.

  Now, the ocean is both your prison and your only hope.

  - Stay human to fish safely from the pier and build the foundation
    of your fortune.
  - Transform into a fish to dive into the depths, where glowing chests
    and forgotten treasures lie scattered across the seabed.
  - Risk everything to grow richer faster... or lose it all to the
    predators lurking below.

  The Church does not care how you earn the money.

      Only that you do.

  Every coin you collect drags you closer to freedom. Every lost treasure
  tightens the chains that bind you to this place.
  And somewhere, far beyond the waves, a ledger waits to be cleared.

      Reach 1,000,000,000 coins and your debt will be forgiven.

  Fail... and this island will become your permanent grave.

      The ocean is no longer just calling. It is demanding payment.


================================================================================
  PROJECT STRUCTURE & ARCHITECTURE
================================================================================

  Game
   |-- SceneManager              scene lifecycle & transitions
   |    |-- Scene (general)
   |         |-- MapHandler      map loading, tile drawing,
   |         |                   interactable object spawning from file
   |         |-- InteractableObjects (general)
   |         `-- Entity (base)
   |
   |-- Player                    state pattern
   |    |-- HumanState           top-down movement & interaction
   |    `-- FishState            platformer movement & interaction
   |
   |-- HUD                       renders texts, boxes and buttons
   |-- Camera2D                  follows player
   |-- AudioManager              background music + sfx
   |-- SaveSystem                key=value .txt save/load
   `-- Text                      custom bitmap font renderer


  Data types
  ----------
  Fish            rarity (Common / Rare / Epic / Legendary) + value
  ChestObject     type + value
  PlayerVisual    Human / Fish  (drives sprite & state)
  SceneType       Enum of all scenes
  PrintableText   text, pos, scale, isStatic, background
  PrintableBox    pos, size, clr, isStatic, filled


================================================================================
  SAVE SYSTEM
================================================================================

  - Simple key -> double map (unordered_map<string, double>)
  - Saved as key=value lines in a human-readable text file (gameSave.txt)
  - CTRL + T resets to defaultGameSave.txt


================================================================================
  AUDIO SYSTEM
================================================================================

  - Background music
  - Sound effects


================================================================================
  DIRECTORY STRUCTURE
================================================================================

  BUas-Intake/
  |-- assets/      Game files (saves, images, audio)
  |-- src/         Source files of the game
  |-- tmpl8/       Framework template (surface, sprite, vec2)
  |-- lib/         Audio, FreeImage, OpenGL, SDL2
  |-- dlls_x64/    Runtime DLLs (x64)
  `-- dlls_x86/    Runtime DLLs (x86)


================================================================================
  POSSIBLE FUTURE IMPROVEMENTS
================================================================================

  - Better upgrade balancing
  - More fish types and smarter enemy AI
  - Wider variety of shops
  - First-run tutorial overlay
  - Use a database instead of .txt files to store save data


================================================================================
  RESOURCES
================================================================================
  Almost all the assets have been modified by me using Phothop

  Top-Down assets:
    - https://schwarnhild.itch.io/summer-plains-tileset-and-asset-pack-32x32-pixels
    - https://schwarnhild.itch.io/summer-village
    - https://ninjikin.itch.io/trees
    - https://schwarnhild.itch.io/summer-plains-tileset-and-asset-pack-32x32-pixels
  
  2D assets:
    - https://admurin.itch.io/free-chest-animations
    - https://www.reddit.com/media?url=https%3A%2F%2Fi.redd.it%2Fulblga7xeefa1.gif

  Audio:
    - https://tallbeard.itch.io/music-loop-bundle


================================================================================