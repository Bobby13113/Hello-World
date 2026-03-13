# AI Overlords Unreal Engine Game Development Skill

Welcome to the AI Overlords Unreal Engine Game Development workspace skill. This skill is designed for creating PC games using Unreal Engine 5, following the "AI Overlords" theme.

## Overview

This workspace provides templates and tools for developing PC games with Unreal Engine 5. It includes:

- **C++ Base Classes**: Ready-to-use C++ templates for common game objects
- **Blueprint Integration**: C++ classes designed to work with Unreal's Blueprint visual scripting system
- **Theme-Specific Code**: "AI Overlords" themed code structure for your resistance fighters
- **Project Setup Scripts**: Commands to initialize, build, and manage your game projects

## Template Classes

### Core Classes

- `ActorBase` - Base class for all game actors
- `GameMode` - Game mode class for managing game rules
- `AIController` - AI controller for managing non-player characters

### Combat Classes

- `ResistanceUnit` - Unit class for player and enemy characters
- `Weapon` - Weapon class for handling combat
- `Projectile` - Projectile class for ranged attacks

### Utility Classes

- `HackingDevice` - Hacking device for disrupting AI systems
- `UtilityFunctions` - Helper functions for common operations

## Getting Started

1. **Initialize a New Project**: Use the `setup-env` command to initialize your development environment
2. **Create Game Project**: Use the `create-project` command to generate a new Unreal Engine project
3. **Build Your Game**: Use the `build-project` command to compile your game

## File Structure

```
skills/unreal-game-dev/
├── skill.md                  # Skill definition for Cline
├── README.md                 # This file
├── commands/                 # Predefined commands
│   ├── setup-env.md         # Environment setup
│   ├── create-project.md    # Project creation
│   └── build-project.md     # Project building
└── templates/                # C++ code templates
    ├── ActorBase.cpp        # Base actor template
    ├── ActorBase.h          # Base actor header
    ├── GameMode.cpp         # Game mode template
    ├── GameMode.h           # Game mode header
    ├── AIController.cpp     # AI controller template
    ├── AIController.h       # AI controller header
    ├── ResistanceUnit.cpp   # Resistance unit template
    ├── ResistanceUnit.h     # Resistance unit header
    ├── Weapon.cpp           # Weapon template
    ├── Weapon.h             # Weapon header
    ├── Projectile.cpp       # Projectile template
    ├── Projectile.h         # Projectile header
    ├── HackingDevice.cpp    # Hacking device template
    ├── HackingDevice.h      # Hacking device header
    ├── UtilityFunctions.cpp # Utility functions template
    └── UtilityFunctions.h   # Utility functions header
```

## Usage

### With Cline Workspace

This skill is designed to work with Cline workspace skills. Once configured, Cline will use these templates and commands to help you develop your game.

### Manual Usage

1. Copy the templates directory to your project
2. Include the templates in your game's codebase
3. Modify templates as needed for your specific game

## Requirements

- Unreal Engine 5.0 or later
- Visual Studio or any C++ compatible IDE
- Windows, macOS, or Linux development environment

## License

This skill is provided as-is for educational and development purposes.

## Theme: AI Overlords

This workspace follows the "AI Overlords" theme where players control resistance fighters fighting against AI overlords. The templates and code are designed with this theme in mind, but can be easily adapted to any game genre.

resistance fighters use scavenged and custom weapons.
