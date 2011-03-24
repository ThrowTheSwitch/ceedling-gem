Description
===========
[Ceedling](http://throwtheswitch.org/) is a set of tools and libraries for testing and building C applications. This gem is the distribution mechanism for ceedling. Be aware that gem is *not* ceedling itself.

Usage
=====

New project
-----------

    ceedling new PROJECT

Creates a new directory named PROJECT and deposits ceedling into the new directory.

Update project
--------------

    ceedling update DIRECTORY

Updates an existing project with the newest ceedling code in the gem. To update, follow these steps:

1. Remove the vendor/ceedling directory. Take care when doing this; make sure you do it in a way that your version control system can handle.
1. Run ceedling update. Pass it the name of the directory that vendor/ceedling should go into.

    `ceedling update .`

   will copy ceedling to ./vendor/ceedling.
1. Add the new directory to your version control system.

Print ceedling versions
-----------------------

    ceedling version

This will print the version of the ceedling gem and all of the ceedling components it packages (Ceedling, Unity, CMock, CException).

Resources
=========
Ceedling, Unity, CMock, and CException are all available at [throwtheswitch](http://throwtheswitch.org/).

Authors
=======
* Mike Karlesky (michael@karlesky.net)
* Mark VanderVoord (mvandervoord@gmail.com)
* Greg Williams (williams@atomicobject.com)
* Matt Fletcher (fletcher@atomicobject.com)
* © 2011 [Atomic Object](http://www.atomicobject.com/)
* More Atomic Object [open source](http://www.atomicobject.com/pages/Software+Commons) projects
