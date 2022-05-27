REPO:

- Link to repository: https://github.com/Oliverlam2/Minigin-Engine-Repo

DESIGN CHOICES:

- Command:
-> I used Commands in response to user-inputs for QBert's and Coily's (when in versus mode) movement.
-> I also used them for score events: when Coily dies, when remaining Discs need to be added at the end of each level, when a tile is activated and when QBert catches Slick or Sam.
-> Lastly, I used a command which kills QBert. I give this command to purple enemies so that when they come in contact with QBert, they can execute this command.

- Flyweight:
-> I use the Flyweight pattern when I'm rendering my level-grid. In my class I keep a vector of base Tile-type pointers and one shared pointer for each possible tile texture (the shared pointers represent the intrinsic state).
-> When I render all of my tiles, I first check the tile type and then render it using that 1 shared pointer to the corresponding texture.

- Observer:
-> I made a LivesDisplay observer which keeps track of player 1- and player 2-QBert's lives. Whenever QBert dies, that event is sent to this observer and a life is subtracted. When there are no lives left, this observer marks the current scene for deletion so that the player is returned to the main menu scene in the next frame.
-> A ScoreDisplay observer works in a similar way to the LivesDisplay one. It keeps track of both players' scores.
-> A Resetter observer is used to reset all of the enemies whenever QBert dies. So when QBert dies, that event is sent to all observers and this one uses that event to reset all the enemies in the level.

- Singleton:
-> I didn't implement any new Singletons, but I did use the ones that were already implemented.
-> I adjusted the SceneManager a bit so that it can mark the currently active scene for deletion. When this occurs, all of the level scenes are removed from the scenemanager in the next frame and the main menu scene is activated again.
-> I also added a method that allows you to activate the next scene whenever the current scene's termination condition has been reached.
-> The ActivateFirstScene method kickstarts the scene handling process.

- State:
-> I used the State pattern for Coily's different states.
-> Coily can have an InvisibleState, an EggState and a SnakeState.
-> When a Coily is spawned, its initial state is the InvisibleState. This state uses a timer to count towards a threshold after which it sets Coily's visiblity to true and returns a pointer to a new EggState object.
-> Coily's EggState moves Coily toward the bottom of the pyramid using a random direction each time. After it reaches the bottom, it returns a pointer to a new SnakeState object.
-> The SnakeState is Coily's final state and it moves Coily in the direction of QBert's current position.
-> When Coily dies, its state is reset to the InvisibleState.

- Double Buffer:
-> I used the Double Buffer pattern inside of QBert's movement component because enemies need to be able to read QBert's current position, but if a player's input changes QBert's position, then that position changes, then QBert has to update its sprite based on that new texture in the Render method, but before that happens the enemies already use QBert's new position as a target position. This results in QBert and an enemy being able to collide in code, but not on screen.
-> The solution to this was to use OldRow and OldCol data members and normal Col and Row data members for QBert. OldRow and OldCol represent the current buffer (which enemies can read from) and Row and Col represent the next buffer (which are written to when they need to be updated).
-> Whenever QBert's update method is called the 2 buffers are swapped.

- Game Loop:
-> The Game Loop is put up in a way so that user input and CPU speed don't affect game progression.
-> My ProcessInput method determines whether or not the Game Loop is finished.
-> At the end of each loop, the current thread is idle for a duration based on the MsPerUpdate variable so that there is a consistent duration of time in each loop.

- Update Method:
-> Each GameObject has its own Update method in which it updates all of its Components through their polymorphic Update method.

- Component:
-> Each GameObject is built out of a number of components. Each component has a unique purpose. This way each code domain is not coupled to others.

- Event Queue:
-> I used an Event Queue for my audio thread. Whenever the PlaySound or PlayMusic method is called, the event queue first checks if that sound is already in the queue. If it is, but it has a louder volume, the volume of the existing sound is changed.
-> I made a separate "audio" thread which has an event loop. In this event loop the first element in the queue is processed and removed each frame.

- Service Locator:
-> I used a Service Locator for my audio system. It makes the Simple-SDL-2 audio service globally available while still hiding its actual type.