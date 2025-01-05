# Image Conversion

## Included Script

Use the included `imgConverter.py` script to convert an image to a C byte-array. It will automatically resize the image to the dimensions of the TFT display.


```
usage: ImageConverter [-h] [--color {RGB,RGBA,BGR,BGRA,GRAY,HSV,XYZ}] IMAGEFILE

Converts an image into a bytearray

positional arguments:
  IMAGEFILE             image to be converted

options:
  -h, --help            show this help message and exit
  --color, -c {RGB,RGBA,BGR,BGRA,GRAY,HSV,XYZ}
                        color space of the original image (defaults to RGB)
```


## Original Tool used by Lilygo

The original conversion tool used by Lilygo can be found [here](https://github.com/Xinyuan-LilyGO/T-Display-S3/blob/main/tools/Image2Lcd.zip).


The correct settings are:
* Scan mode: Horizon scan
* BitsPixel: 16-bit TrueColor (first option)
* Max Width and Height: 160x80
* Include head data: off
* Scan Right to Left: off
* Scan Bottom to Top: off
* MSB First: on


The 16-bit color tab should have R5G6B5 selected.
