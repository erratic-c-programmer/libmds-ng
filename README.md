# libmds-ng
Library for misc. data structures, completely rewritten, as the old
version was full of bugs and had no proper return statuses, etc. I might
rename it to libmds when it's ready.

## Features:
- Written in pure C
- Has data structures:
	- vector
	- llist
	- string [NOT YET]
- Allocates lots of stuff on heap, so may be slightly slower.
- Quite memory-efficient (I think?)

## Building
### Prerequisites:
- gcc/clang/tcc/whatever C99 compiler
- GNU make

To build static and dynamic libraries with tests:
```linux
$ make
```

## Documentation generation:
Go to the subdirectory docs and create the directory `html`,
and run `naturaldocs2 .` (Of course, this requires that you have
[naturaldocs2](https://www.naturaldocs.org/) installed)

# Warranty (or lack of it)
No warranties, either express or implied, are hereby given. All
software is supplied as is, without guarantee.	The user assumes all
responsibility for damages resulting from the use of these features,
including, but not limited to, frustration, disgust, system abends, disk
head-crashes, general malfeasance, floods, fires, shark attack, nerve
gas, locust infestation, cyclones, hurricanes, tsunamis, local
electromagnetic disruptions, hydraulic brake system failure, invasion,
hashing collisions, normal wear and tear of friction surfaces, comic
radiation, inadvertent destruction of sensitive electronic components,
windstorms, the Riders of Nazgul, infuriated chickens, malfunctioning
mechanical or electrical sexual devices, premature activation of the
distant early warning system, peasant uprisings, halitosis, artillery
bombardment, explosions, cave-ins, and/or frogs falling from the sky.
