# Nadetech-to-Cheersonic-USC

Hardware and software needed to upgrade a Nadetech Ultrasonic Spray Coater with Cheersonic components.

Please refer to [this project's Wiki](https://github.com/giacomos97/Nadetech-to-Cheersonic-USC/wiki) for all the technical details and instructions.

## Description

Nadetech no longer offers support for their ultrasonic spray coating equipment. If you have experienced failure of the ultrasonic nozzle components, you may consider replacing them with components from another manufacturer. This project aims to upgrade the ultrasonic generator and nozzle of a Nadetech Ultrasonic Spray Coater with Cheersonic components.

The primary objective is to replace the existing ultrasonic spray system with the Cheersonic Ultrasonic Spray System UCA120. The key challenge is ensuring compatibility between the new Cheersonic system and the existing Nadetech equipment. This requires an ad-hoc interface because the current PiezoDrive generator is controlled via an RS485 interface, while the Cheersonic equipment employs a 2-wire control line.

The Nadetech electronics continuously communicates via the RS485 interface with the PiezoDrive ultrasonic generator. If this communication fails, the equipment will not perform the ultrasonic deposition. Therefore, an intermediary solution (like an Arduino) is required to manage on/off commands.

This project provides guidance and detailed instructions for installation and usage. The project involves replacing the existing PiezoDrive controller and nozzle with the Cheersonic system and includes detailed instructions for hardware and software upgrades, a list of components required for the upgrade, and installation and setup guides.

## Contributing

We welcome any contributions, improvements, or bug reports to this project. Your input is valuable and helps improve the project for everyone.

## Disclaimer

Please note the following:

- This project is not affiliated with Cheersonic or Nadetech.
- Be aware of the potential consequences of this upgrade operation, as you may irreparably damage your equipment.
- Perform any action at your own risk. Neither Cheersonic nor Nadetech is available to provide technical assistance for this project.
