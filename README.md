# Restaurant IoT System

## Overview

This repository contains the code and documentation for a **wireless restaurant assistance system**. The system is composed of three main devices:

1. **Ring Button** – Placed on each dining table. When pressed by a customer, it sends a notification via the wireless network.
2. **Watch** – Worn by a waiter or staff member, receives table alerts and can send acknowledgments or messages to the gateway.
3. **Gateway** – Manages a Sub-1 GHz mesh network connecting all ring buttons and watches. It handles:
   - Network formation and table assignments
   - Routing messages to the corresponding waiter’s watch
   - Optional forwarding to a **Supervisor** watch

## Key Features

1. **Sub-1 GHz Mesh Network**  
   - Uses a low-power, long-range wireless protocol suitable for indoor restaurant environments.
   - The gateway creates and manages the network, ensuring reliable communication between ring buttons and watches.

2. **Table Assignment**  
   - Each ring button is linked to a specific table number.  
   - The gateway knows which waiters are responsible for which tables and routes button-press alerts accordingly.

3. **Supervisor Mode**  
   - Any watch can be designated as a **Supervisor** via the gateway’s configuration.  
   - The Supervisor watch receives copies of all ring button alerts and waiter acknowledgments, providing an overview of the entire restaurant floor.

4. **Simple Interaction**  
   - **Ring Button**: Single press from the customer triggers an immediate alert to the assigned waiter’s watch.  
   - **Watch**: Receives alerts with table number; can optionally acknowledge or forward messages.  
   - **Gateway**: Processes incoming alerts, manages user/device assignments, and synchronizes data across the network.

5. **Scalable & Modular**  
   - Supports multiple gateways if needed (e.g., one per floor in a large restaurant).  
   - Additional ring buttons and watches can join the network with minimal reconfiguration.

6. **Low Power Operation**  
   - Designed for extended battery life on the ring button and watch devices.  
   - Efficient Sub-1 GHz protocol keeps transmissions short and infrequent, only sending data on button press or acknowledgment.

## Project Structure

- **Branch: `watch`**  
  Contains firmware and software resources needed to build the watch device application.  

- **Branch: `ring_button`**  
  Contains firmware and software for the customer’s table button device.  

- **Branch: `gateway`**  
  Contains firmware and software to run on the central gateway (coordinator) device.

## Getting Started

1. **Clone the Repository**

   ```bash
   git clone https://github.com/your-org/restaurant_iot_system.git
