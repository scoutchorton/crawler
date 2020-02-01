# Crawler
Crawler is a terminal based dungeon crawling adventure game, inspired by the mobile game 1-Bit Rogue ([Apple App Store](https://apps.apple.com/us/app/1-bit-rogue-a-dungeon-crawler-rpg/id1128070374) and [Google Play Store](https://play.google.com/store/apps/details?id=one.bit.rogue&hl=en_US)).

Crawler is made possible mainly through the ncurses library. This project was brought forth as a result of my C/C++ class for college.

# Source Installation
### Linux and Mac OS:
*Not tested on Mac OS*
#### Prerequisites
* gcc
* libncurses5
* libncursesw5
* libncurses5-dev
* libncursesw5-dev

#### Installation
```bash
# You may also use the SSH address: git@github.com:scoutchorton/crawler.git
$ git clone https://github.com/scoutchorton/crawler.git
$ cd crawler
$ ./compiler
```
* **NOTE:** This does not install the program to the system. Every time you'd like to run the program, you must go to the directory where `git clone` downloaded to, and run `./crawler`.

#### Updating
```bash
$ cd <path-to-cloned-repo>/crawler
$ git pull
$ ./compiler
```