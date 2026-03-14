# AI Overlords Game Design Notes

## Game Overview

### Theme

The "AI Overlords" game is set in a near-future dystopia where humanity fights against an oppressive AI统治. Players take on the role of resistance fighters using scavenged technology and custom weapons to disrupt AI systems.

### Core Gameplay Loop

1. **Explore**: Navigate the global Earth map
2. **Hack**: Use hacking devices to disrupt AI systems
3. **Combat**: Fight against AI-controlled enemies
4. **Upgrade**: Improve weapons and gear with scavenged parts

### Game Style

**Top-Down Earth Map Scroller**

- Camera views Earth from above
- Scrollable map with lat/long coordinates
- World map size: 20,000 x 10,000 units
- Camera zoom levels: 500-2000 units
- Mouse and keyboard controls

## Character System

### Resistance Units

- **Health System**: Resistance units have configurable health points
- **Movement**: Fast and agile for hit-and-run tactics
- **Weapons**: Customize with scavenged and custom weapons
- **Top-Down Movement**: WASD or arrow keys to move

### AI Overlords

- **Enemy AI**: Uses the AIController template for behavior
- **Patrol Patterns**: Predefined patrol routes
- **Combat AI**: Aggressive and adaptive

## Map System

### Earth Map Generator

- **Grid System**: 100-unit grid cells
- **Terrain Types**: Plains, forests, mountains, water
- **City Locations**: Major world cities at lat/long coordinates
- **Terrain Features**: Rivers, lakes, forests

### Map Features

- **Lat/Long Coordinate System**: Real Earth coordinates mapped to game world
- **Grid-Based Terrain**: Tiles for terrain types
- **City Placement**: Major world cities
- **Dynamic Loading**: Load map sections as player moves

### Camera System

- **Orthographic View**: Top-down perspective
- **Smooth Following**: Camera follows player unit
- **Zoom Control**: Mouse wheel zoom (500-2000 units)
- **Pan Controls**: Mouse drag or keyboard

## Combat System

### Weapon Types

1. **Ranged Weapons** -使用 projectile template
   - Customizable damage and accuracy
   - Ammo management
   - Top-down aiming

2. **Melee Weapons**
   - Fast but short range
   - No ammo needed
   - High risk, high reward

### Projectile System

- **Types**: Bullets, lasers, rockets
- **Effects**: Trail effects, explosion effects
- **Collision**: Configurable hit detection

## Hacking System

### Hacking Devices

- **Hacking progress**: Visual feedback during hacking
- **Range**: Limited hacking range
- **Interference**: Enemies can interrupt hacking

### Hack Effects

- **Disable AI**: Temporarily disable enemy AI
- **Reveal Location**: Show enemy positions
- **Override Systems**: Control enemy units

## Game Modes

### Single Player

- Campaign mode with story progression
- Enemy waves with increasing difficulty
- Resource management and upgrades

### Multiplayer (Optional)

- Co-op hacking missions
- PvP hacking competition
- Team-based objectives

## Visual Design

### Art Style

- **Resistance Fighters**: Scavenged armor and gear
- **AI Overlords**: Sleek, technological design
- **Environment**: Dystopian urban landscape

### Effects

- **Hacking**: Glowing blue energy effects
- **Combat**: Fire and explosion effects
- **Damage**: Visual feedback on hit

## Audio Design

### Sound Effects

- **Weapons**: Distinct sounds for each weapon type
- **Hacking**: Electronic and mechanical sounds
- **Environment**: Immersive ambient sounds

### Music

- **Tense**: Combat and hacking sequences
- **Exploration**: Atmospheric background music
- **Success**: Victory and achievement themes

## Technical Considerations

### Performance

- **Optimization**: Level of detail (LOD) systems
- **Memory**: Efficient asset loading and unloading
- **Frame Rate**: Target 60 FPS

### Scalability

- **Settings**: Configurable graphics quality
- **Resolution**: Support for multiple screen sizes
- **Controls**: Customizable input bindings

## Future Enhancements

### Planned Features

1. **Vehicle System**: Drive vehicles into battle
2. **Base Building**: Establish resistance bases
3. **Tech Tree**: Unlock new weapons and upgrades
4. **Stealth Mechanics**: Infiltration and sabotage

### Potential Expansions

- **New Enemies**: Different AI types and behaviors
- **New Weapons**: Experimental weapon prototypes
- **New Environments**: Different terrain types
- **New Game Modes**: Challenge and survival modes
