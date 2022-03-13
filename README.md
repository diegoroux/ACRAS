# ACRAS

A way to get audio working on a Chromebook running Linux is using CRAS (Chromium OS Audio Server).
Unfortunately CRAS doesn't change the output when you (un)plug your headphones, Automatic CRAS (ACRAS) tries to fix this.

## Prerequisites

- [CRAS](https://chromium.googlesource.com/chromiumos/third_party/adhd/+/refs/heads/main/cras/)
- [acpid2](https://sourceforge.net/projects/acpid2/)

## Getting started

Clone this repo

`git clone https://github.com/diegoroux04/ACRAS`

Compile

`make`

Install

`sudo make install`

## Contributing and Issues

Thanks for your interest in contributing! Please refer to [the contributing guide](CONTRIBUTING.md) on how to get started.

## LICENSE

ACRAS is licensed under the [MPL v2](LICENSE).
