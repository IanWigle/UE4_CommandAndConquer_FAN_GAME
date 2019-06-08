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
		
	Tiberium
		Crystal 'grows' through three different levels. When at max level it will create another crystal.
		Spawner will keep track of the number of crystals in it's pool, preventing the pools from growing to no end.
		
	Tech Tree
		Tech Tree for NOD is established.
		

TODO (Code In order of priority):

	Istablish remaining structures for both GDI and NOD.

	Finish behavior trees for units to attack things.
	Finish behavior trees for defenses to attack things.
	
	Clean up code in both C++ and blueprints.
	
	Setup win condition
	
	Setup single player lobby that will save data to game instance for game propeerties.
	
TODO (Models)

	NOD:
			Light Tank
			Artillery

			All infantry
			All Aircraft

			Silo
			Sandbags
			ChainLink
			Concrete Wall
			Advanced Power
			Finish Yard
			Obelisk
			Temple
			
	GDI:
	
			EVERYTHING
			