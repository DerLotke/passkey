#!/usr/bin/python

import sys
import re
import argparse
import cv2
import numpy as np
from pathlib import Path


def main(arguments):
    img = cv2.imread(arguments.input)
    img = cv2.resize(img, (160, 80), interpolation=cv2.INTER_LINEAR)

    # Always use an RGB image as the base
    if arguments.color_space == "RGB":
        pass
    elif arguments.color_space == "RGBA":
        img = cv2.cvtColor(img, cv2.COLOR_RGBA2RGB)
    elif arguments.color_space == "BGR":
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    elif arguments.color_space == "BGRA":
        img = cv2.cvtColor(img, cv2.COLOR_BGRA2RGB)
    elif arguments.color_space == "GRAY":
        img = cv2.cvtColor(img, cv2.COLOR_GRAY2RGB)
    elif arguments.color_space == "HSV":
        img = cv2.cvtColor(img, cv2.COLOR_HSV2RGB)
    elif arguments.color_space == "XYZ":
        img = cv2.cvtColor(img, cv2.COLOR_XYZ2RGB)
    else:
        print("Unknown color format", file=sys.stderr)
        return -1

    R5 = (img[...,0]>>3).astype(np.uint8).byteswap().astype(np.uint16)
    G6 = (img[...,1]>>2).astype(np.uint8).byteswap().astype(np.uint16) << 5
    B5 = (img[...,2]>>3).astype(np.uint8).byteswap().astype(np.uint16) << 11

    RGB565 = R5 | G6 | B5
    rgb_bytes = RGB565.flatten().byteswap().tobytes()

    # Pretty-print the bytes
    hexified_str = ", ".join(f"{b:#0{4}x}" for b in rgb_bytes) # convert bytes to comma-seperated hex strings
    with_newlines = re.sub("(.{66})", "\\1\n", hexified_str, flags=re.DOTALL) # add newline each 66 characters
    with_newlines = re.sub(" \n", "\n    ", with_newlines, flags=re.DOTALL) # adjust whitespace
    with_newlines = f"    {with_newlines}"

    print(f"uint8_t const {Path(arguments.input).stem}[25600] = {{")
    print(with_newlines)
    print("}")

    print(len(rgb_bytes), file=sys.stderr)
    return 0


if __name__=="__main__":
    parser = argparse.ArgumentParser(
        prog="ImageConverter",
        description="Converts an image into a bytearray"
    )
    parser.add_argument("input", metavar="IMAGEFILE",
                        help="image to be converted")
    parser.add_argument("--color", "-c",
        choices=["RGB", "RGBA", "BGR", "BGRA", "GRAY", "HSV", "XYZ"],
        default="RGB",
        dest="color_space",
        help="color space of the original image (defaults to %(default)s)")
    exit(main(parser.parse_args()))
