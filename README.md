# UE4_CommandAndConquer_FAN_GAME

Current functionalities:

	Can build structures and defenses. 
		Constructed buildings and defense will affect player's power.
		Structures do affect nav-mesh for unit navigation.
	
	Production buildings will spawn units.
		Currently only NOD Airfield is set up for vehicle spawning.
	
	Units can be selected and told to move to different locations.
		Harvester has unique behavior tree to automaticly search for tiberium resource.
	
	Graphics Settings
		Can change shadow quality, texture quality, and AA.
		
	Audio Settings
		Is there but needs revision.
		Audio settings seem to not affect game.
		
	Tiberium
		Crystal 'grows' through three different levels. When at max level it will create another crystal.
		Spawner will keep track of the number of crystals in it's pool, preventing the pools from growing to no end.
		
	Tech Tree
		Tech Tree for NOD is established.
		

TODO (Code In order of priority):

	Establish remaining structures for both GDI and NOD.

	Finish behavior trees for units to attack things.
	Finish behavior trees for defenses to attack things.
	
	Redo Audio settings and audio component for music.
	
	Clean up code in both C++ and blueprints.
	
	Setup win condition
	
	Setup single player lobby that will save data to game instance for game properties.
	
TODO (Models)

	GLOBAL:
	
			Silo
			Sandbags
			ChainLink
			Concrete Wall
			Advanced Power
			Finish Yard

	NOD:
			Light Tank
			Artillery

			All infantry
			All Aircraft
			
			Temple
			
	GDI:
	
			EVERYTHING
			
Current Plugins in use with project/engine:

	Horizon UI Plugin
	Save Extension
	Export PNG
	
			
For a more updated TODO:
https://trello.com/b/boiXCwAf/ue422-commandconquer
			
