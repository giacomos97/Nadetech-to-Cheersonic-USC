# Nadetech-to-Cheersonic-USC

Hardware and software needed to upgrade a Nadetech Ultrasonic Spray Coater with Cheersonic components.

## Description

Nadetech no longer offers support for their ultrasonic spray coating equipment. If you have experienced failure of the ultrasonic nozzle components, you may consider replacing them with components from another manufacturer. This project aims to upgrade the ultrasonic generator and nozzle of a Nadetech Ultrasonic Spray Coater with Cheersonic components.

The primary objective is to replace the existing ultrasonic spray system with the Cheersonic Ultrasonic Spray System UCA120. The key challenge is ensuring compatibility between the new Cheersonic system and the existing Nadetech equipment. This requires an ad-hoc interface because the current PiezoDrive generator is controlled via an RS485 interface, while the Cheersonic equipment employs a 2-wire control line.

The Nadetech electronics continuously communicates via the RS485 interface with the PiezoDrive ultrasonic generator. If this communication fails, the equipment will not perform the ultrasonic deposition. Therefore, an intermediary solution (like an Arduino) is required to manage on/off commands.

This project provides guidance and detailed instructions for installation and usage. The project involves replacing the existing PiezoDrive controller and nozzle with the Cheersonic system and includes detailed instructions for hardware and software upgrades, a list of components required for the upgrade, and installation and setup guides.

## Setup Overview

![Schematic overview of the standard and the new setups](./resources/upgrade_overview.png)

### Standard Setup

* Computer -> Nadetech electronics -> PiezoDrive USC generator -> Default Nadetech nozzle.

### New Setup

* Computer -> Nadetech electronics -> Arduino -> Cheersonic USC generator -> Cheersonic nozzle.
* The Arduino acts as an intermediary to facilitate communication between the Nadetech electronics and the Cheersonic USC generator.

The circuit diagram shows the connections between the Arduino, MOSFET, resistors, Cheersonic control line, and Nadetech RS485 interface. Key components include:

* Arduino Uno
* Breadboard
* MOSFET (IRLZ44N)
* Resistors (100 kohm and 120 ohm)
* Connections to the Cheersonic control line and Nadetech RS485 interface.

## Features

* Detailed instructions for hardware and software upgrades.
* List of components required for the upgrade.
* Installation and setup guides.

## Bill of Materials

Consider the following bill of materials as reference for this project. Additionally, you will need to purchase a Cheersonic Ultrasonic Spray System UCA120 from your local reseller. Ensure that a 2-wire control line is provided with your purchase. Cheersonic will also provide a customized nozzle fixture to allow their nozzle to be installed on your Nadetech equipment. Please provide them with the necessary measurements.

| Description                              | Manufacturer code | Quantity   |
|------------------------------------------|-------------------|------------|
| Arduino Uno Rev 3                        | A000066           | 1 unit     |
| Breadboard for Pico Monk Makes           | SKU00089          | 1 unit     |
| Seeed Studio Grove - RS485               | 103020193         | 1 unit     |
| Jumper wires, male-male                  | 4110-40           | 20 units   |
| RS PRO PCB Terminal Block                | 304-03-516        | 5 units    |
| Power Supply for Arduino, 12 V, 1000 mA  |                   | 1 unit     |
| 100 kΩ resistor                          |                   | 1 unit     |
| 120 Ω resistor                           |                   | 1 unit     |
| USB Cable for Arduino                    |                   | 1 unit     |
| IRLZ44N MOSFET                           | IRLZ44NPBF        | 1 unit     |

## Installation

**Software**

1. Connect the Arduino board to your computer via USB.

2. Flash the [firmware](./Nadetech_Cheersonic_interface/Nadetech_Cheersonic_interface.ino) on your Arduino board.

3. Your board is ready to be used. You will no longer need the USB interface, as power will be provided from the 12 V external supply.

**Hardware**

1. After flashing the Arduino firmware, connect the electrical components as represented in the following [circuit diagram](./resources/circuit_diagram.png).

   ![Schematic of electronic circuit](./resources/schematic.png)

## Usage

Under construction.

## Contributing

We welcome any contributions, improvements, or bug reports to this project. Your input is valuable and helps improve the project for everyone.

## Disclaimer

Please note the following:

- This project is not affiliated with Cheersonic or Nadetech.
- Be aware of the potential consequences of this upgrade operation, as you may irreparably damage your equipment.
- Perform any action at your own risk. Neither Cheersonic nor Nadetech is available to provide technical assistance for this project.