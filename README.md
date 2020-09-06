# GBJAM8 (The Binding of Isaac: Game Boy Edition)

A demake for the *classic roguelike* **The Binding of Isaac** originally developed by
**Edmund McMillen** and **Florian Himsl**. This homebrew redesign of the game was built
from the ground up to run on the orignal **Game Boy** hardware itself *(meaning it will
require an emulator to play on the PC)*.

The project was made for 2020's **[#GBJAM8](https://itch.io/jam/gbjam-8)** and is more
of a prototype as to what the game would be like running on original **Game Boy**
hardware so, many features may be missing or lacking polish. Hopefully, in the future,
this project could be fleshed out more into a well-rounded and enjoyable experience.

You can find a download for the game's ROM file over on
**[itch.io](https://jrob774.itch.io/the-binding-of-isaac-game-boy-edition)**.

## Development

The project was developed using C and the **[GBDK](https://github.com/Zal0/gbdk-2020)**
library to compile into a Game Boy ROM. All other code was written from scratch for this
project. Tools such as **[GBTD (Game Boy Tile Designer)](https://www.devrs.com/gb/hmgd/gbtd.html)**,
**[GBMB (Game Boy Map Designer)](https://www.devrs.com/gb/hmgd/gbmb.html)**, and
**[GameBoyPngConverter](https://github.com/gingemonster/GameBoyPngConverter/)** were
used to create and generate tile graphics, maps, and splash screens for the project. All
of these tools are available as open source from their respective links.

## Building

All dependencies are included with the project so the only step needed is to run the
`build/build.bat` file in order to create the output binary. The resulting GB ROM will
require an emulator in order to be executed. I recommend **[BGB](https://bgb.bircd.org/)**
as it has a larger number of useful features and is extremely accurate to the hardware
of the **Game Boy**. Note that this build process works on **Windows** only and has not
been setup for either **Linux** or **MacOS**. However, porting the project over to these
platforms should be relatively simple to do.

## License

The project's code is available under the **[MIT License](https://github.com/JRob774/gbjam8/blob/master/LICENSE)**.

*The **Binding of Isaac** IP and all of its characters are owned by its respective copyright holders
and I claim no ownership, this is simply a fan project made both for fun and educational purposes.*
