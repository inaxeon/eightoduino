This is the source code for an Intel 8086 based micro board

Full details are here:
http://tech.mattmillman.com/projects/8od/

Directory contents:

app_*:

Example "boot from flash" applications for 8OD.

bootrom:

The source code for 8OD's standard bootrom which is used
for serial download, to and booting from SPI flash.

eprom_with_app:

Contains an example of how to make an image which runs from
EPROM instead of using the standard bootrom. RAM is still
required to store the stack and data.

Interrupts are not currently supported.

sys:

Sources used by all other subdirectories

*** CAVEAT EMPTOR ***

All code here must be compiled with Open WATCOM version 1.7a

I have tried newer versions - my findings:

Version 1.8
Version 1.9

* Copy attribute (linker script) seems to be broken.
  Linker does not copy data from source segment to destination
  segments, breaking the bootrom builds.

* There seems to be some kind of new enforcement mechanism
  which checks that no code or data lies outside of the active 64KB
  segment. 8OD apps technically do have a little of this to assist
  the bootstrapping process, but it is not an actual problem.
  'wlink' in these versions believes otherwise, and fails to link.

Version 2.0 BETA

* Still has the copy attribute bug

* The segment extent enforcement seems to have disappeared in this
  version, promising...
  
* When I tried to build an app, the .hex were mostly garbage data with
  the majority of the exectuable code missing, suffice to say that this
  version is completely unuseable (at the time I tried it).

Version 1.7a observed problems

* This version isn't perfect either. See in 'app_gravitech_shield' where
  I have had to add dummy code to stop the linker from crashing. I spent
  quite a lot of time investigating this and never got to the bottom
  of it.

