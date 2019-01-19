# Slide-Bar

Simple board for a slide potentiometer and visible feedback.

<img src="https://github.com/zookzook/Slide-Bar/raw/master/gfx/schema.pdf" width="600">

The idea behind it: With a slide potentionmeter an analog value can be changed. The change or the value is displayed with a bar display (10 LEDs). The board is designed so that you can connect several to each other. The power supply is thus forwarded from board to board.

You can thus combine the components. If you have three of the sliders, you can use the three analog values for one RGB LED. With the three slide potentionmeter thus a certain color can be adjusted.

Okay, that's a bit boring, but great fun for kids. If you add a chic frame and a nice instrument plate to the whole thing, you get a super game for children who like to fiddle around everywhere. Ultimately, that's the idea: a simple game machine and different input components (sliding and turning meters, switches) and output components (RGB LEDs, bar LEDs) with different effects (animated, cursor, Zini mode).

# How does it work?

The whole thing is controlled by an Attiny85 chip. With the help of two shift registers the LEDs are controlled. A rotary potentiometer controls the mode. There are six modes:

1) Standard slider mode: The value is displayed from bottom to top with the LEDs switched on.
2) Analogous to mode 1. The active LEDs are animated pulsatingly. In the red area, the pulse rate is higher.
3) Cursor mode. The value is displayed as a blinking cursor. If the potentiometer is changed, the flashing will be deactivated during the modification time.
4) Zini mode. When the value changes, the cursor moves, pulling a tail behind it. The previously visited LEDs are slowly faded out.
5) still in the planning stage
6) still in the planning stage

The power comes from a USB-A cable. Each two pin headers for 5V + and GND are located on the sides, so that the boards can be placed side by side or one below the other.

# Board preview
<img src="https://github.com/zookzook/Slide-Bar/raw/master/gfx/slide-bar.png" width="600">
