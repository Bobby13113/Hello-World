# Unreal Engine Game Development Skill

## Overview

This skill provides tools, templates, and commands for developing **"AI Overlords, Resistance is Futile"** using Unreal Engine.

## Available Commands

### Environment Setup

- `setup-env`: Initialize the development environment with proper structure and configuration

### Project Creation

- `create-project`: Generate a new Unreal Engine C++ project structure
- `create-level`: Create a new game level with AI Overlords-themed assets
- `build-project`: Build the project for Windows PC

### Code Generation

- `generate-actor`: Create a new C++ Actor class
- `generate-game-mode`: Create a new Game Mode class
- `generate-ai-controller`: Create an AI Controller for Overlord units
- `generate-utility`: Create utility functions for AI logic

### Git Operations

- `init-git`: Initialize Git repository with proper Unreal Engine configuration
- `commit-changes`: Stage and commit changes with standardized message format

## Templates

### Core Classes

- `ActorBase.cpp/h` - Base Actor class template
- `GameMode.cpp/h` - Game Mode template
- `AIController.cpp/h` - AI Controller template
- `LevelLoader.cpp/h` - Level loading system
- `UtilityFunctions.cpp` - AI Overlords utility functions

### Game-Specific Templates

- `ResistanceUnit.cpp/h` - Player resistance fighter
- `OverlordUnit.cpp/h` - AI Overlord unit
- `BattlefieldAI.cpp` - AI decision-making system

## Best Practices

1. Always run `setup-env` before starting development
2. Use the provided templates for consistent code style
3. Follow Git workflow: branch -> develop -> commit -> merge
4. Build frequently to catch compilation errors early
5. Test on target platform (Windows PC) regularly

## Development Workflow

1. Initialize environment: `setup-env`
2. Create project: `create-project`
3. Develop features using templates
4. Build and test: `build-project`
5. Commit changes: `commit-changes`

## Platform Support

- **Primary**: Windows PC (x64)
- **Target**: Windows 10/11

## Requirements

- Unreal Engine 5.x
- Visual Studio 2022 or later
- CMake 3.20+
- Git 2.30+
