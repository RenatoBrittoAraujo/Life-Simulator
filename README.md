# Life Simulator

A simple SDL2 game about simulating a environment of natural selection where you are just one of the many organisms fighting for survival.

Running normally:
```
make run
```

Running verbose:
```
make runv
```

Running with set framerate:
```
make run framerate=60
```

## Technical Stuff

Messages to future me who intents to keep working on this project:

Anything that is drawable to screen inherits from GameObject or some of it's children. Also noting that not because something is drawable to screen it must inherit from GameObject (for example, a npc can be drawn to screen but it has more features than that, features that have nothing to do with that fact that it's drawable or not, therefore you can separate it's "drawable" side by composition using a specific drawable that inherited from GameObject, which overall is much less cancer to deal with).