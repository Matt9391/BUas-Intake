# Hook & Swim

#### Theme: **Transform**

> A tiny two-mode arcade/adventure where you swap between Human and Fish
> forms → fish for treasure, sell to grow your economy, and survive
> the sea to become rich.

------------------------------------------------------------------------
# How to play

**Controls**

    WASD  - Move (Human and Fish)
    SHIFT - Sprint (hold) / sprint sideways
    F     - Interact with:
              - Shops (Seller, Upgrades)
              - Fishing zones
              - Chests (collect)
    SPACE - Start game (home screen)
    CTRL + T - Reset save (wipe saved progression)

------------------------------------------------------------------------

## 2 Modes

-   **Human** mode
-   **Fish** mode

## Objective

-   earn **coins**
-   **improve** your economy (upgrades, multipliers)
-   **avoid losses** (enemies steal money)
-   become **rich**

### How to earn money

-   Catch **chests** in the sea (treasure)
-   **Fish** at the pier/mole (timing mini-game)

### How to use money

-   To **improve** economy (income multiplier seller)\
-   To **enhance** fish skills (stamina, inventory upgrades)

------------------------------------------------------------------------

# Game main mechanics

## Human mode

-   **Top-down** view & movement
-   Free exploration around town and pier
-   **Fishing** mini-game when on the mole:
    -   timing based → get closer to center to increase rarity
-   **Sell** fish and chests to the Seller to collect coins
-   **Buy** upgrades (stamina, multiplier, inventory size)

## Fish mode

-   **2D platformer** view & movement
-   **Enemies** (shark-like fishes) that can steal coins if they catch
    you
-   **Treasures / Chests**:
    -   chests contain coin value and behave as simple colliders (no
        grab animation required) but they move with **Perlin Noise**
-   **Stamina** system:
    -   sprinting drains stamina; stamina recovers when not sprinting

## Losses / penalties

This game is idle-ish . you don't "die" permanently, but there
are penalties: 
- enemies can **steal** coins (avoid being caught) 
- if coins drop below zero you **lose all chests** in your inventory
------------------------------------------------------------------------


# Story





>For years, you’ve lived a quiet life in a small coastal town, watching ships 
>disappear beyond the horizon and wondering what it would feel like to chase 
>fortune instead of dreaming about it.
>One night, after a violent storm, the sea leaves behind something unusual
>strange **glowing** **chests** scattered across the ocean floor. Fishermen whisper 
>about lost **treasures**, ancient cargo, and currents that carry wealth to those 
>brave enough to dive for it.
>But the sea is never generous **without a price**.
>Equipped with a mysterious ability to **transform** between human and fish, 
>you now possess the ultimate advantage:
>- Stay human to fish **safely** from the pier and build your first **savings**.
>- **Dive into the depths** as a fish to hunt for treasures others cannot reach.
>- Risk everything to grow your fortune faster… or lose it to the predators lurking below
>
>Every coin you earn pushes you closer to a single goal:
>**Become the *richest soul* the coast has ever known.**
>
>Will you play it safe and grow steadily, or embrace the danger and chase
>unimaginable wealth?
>
>***The ocean is calling***

---

# Project structure & architecture

-   `Game` → global manager, scene switching, global UI (achievements,
    save/load)
-   `Scene` base class → `HumanScene`, `FishScene`, `HomeScene`
-   `Player` with state pattern: `HumanState`, `FishState`
-   `MapHandler` → map loading, tile drawing, interactable object
-   `InteractableObject` base → `Seller`, `IncomeMultiplier`,
    `StaminaShop`, `Gate`, `FishArea`
-   `Entity` base →  `Enemy`, `Chest`
-   `Text` utility for drawing text done by me

------------------------------------------------------------------------

# Save system

-   Simple key → double type (e.g. `unordered_map<string,double>`)
-   Saved as `key=value` lines in a text file (human readable and
    editable)
-   Game state saved and loaded on exit/start (coins, multipliers,
    upgrades, inventory counters)
-   Achievements based on coins are re-evaluated on load
------------------------------------------------------------------------
# Possible future improvements

-   Sounds and Music
-   Better upgrade balancing
-   More fish types and smarter enemy AI
-   Wider variety of shop
-   First-run tutorial overlay
-   Better feedback when get stolen
-   Use DB instead of .txt files to store data

