# Just Kill

It's a top-down survival zombie shooter game. You need to survive for as long as possible with your friends.
Tests have been done with 4 players but the game can theoretically handle more.

## Authors
* **Adrià Ferrer** - [Adria-F](https://github.com/Adria-F)
* **Josep Pi** - [joseppi](https://github.com/joseppi)

## Getting Started
- You can revive a fallen ally by staying close to them.
- W,A,S,D for moving your player.
- Use Mouse to aim.
- Left Mouse Button shoot.
- F1 to toggle between Network UI and GUI.
- Shot at zombies to kill them.
- You and the zombies have 1 HP.

## Features
### Adrià Ferrer
- **Entity Interpolation**
	- Fixed Bug: When a player died the interpolation did not stop
- **Input Redundancy**
- Client Side Prediction 
	- Behaviour Implementation
	- Bullet client instancing and server sync
- Animation Module
- Player controller
- Zombie behaviour
	- Path finding
	- Separation
	- Death
- Revive player
	- Multiple player reviving time 
	- Fixed Bug: Players could not revive faster when there where more than one
- Player Names
	- Names of each player are displayed on the top of their Game Object.
	- Can't have two players with the same name.
- In game statistics
	- Zombies killed count
	- Own deaths count
	- Allies revived count
- Client Laser
- Invincibility on spawn
- Release

### Josep Pi

- **Client-side prediction:** contributed local movement and aiming prediction so input can be applied before authoritative server updates arrive.
- **Packet delivery and recovery:** contributed sequence-number tracking, acknowledgements, delivery callbacks and timeout handling in the shared delivery manager. On a failed delivery, replication callbacks requeue the affected commands.
- **Network diagnostics:** extended the ImGui panel with separate dropped-packet counters for replication, ping, welcome and unwelcome messages. Added automatic scrolling to the latest log event.
- **Zombie spawning and session lifecycle:** implemented spawning that increases over time and depends on connected client proxies; reset server/spawner state and removed server game objects when no clients remained.
- **Gameplay and collision:** worked on the map and its collisions, a revive bug fix and updating the collider module.
- **Documentation:** maintained the README.

Selected implementation evidence: [prediction](https://github.com/joseppi/JustKill/commit/afff75684344756d67800314a6b0223d26d405eb), [delivery handling and diagnostics](https://github.com/joseppi/JustKill/commit/0e9be65e8feb456a282ad759a44f656805096d1e), and [spawner/session cleanup](https://github.com/joseppi/JustKill/commit/9f7b414bce82b048456867c7673f2510a77747d8).

Replication, delivery management and reconciliation were shared work; the original joint credits remain below. These are academic implementation contributions, not a claim of production-ready or lossless networking.

### Both
- **Server Replication**
- **Delivery Manager (Replication)**
	- Fixed Bug: Made sure packet drops did not cause any sync problems. (Josep)
- **Server Reconciliation**

## Known Bugs
- Sometimes when you spawn and there are a lot of zombies on the player spawn zone, it can create some issues.
- If the server is minimized, some behaviours could not work properly and client may experience disconnections.
