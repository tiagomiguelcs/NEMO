import asyncio, sys
from bleak import BleakScanner, BleakClient
DEVICE_NAME = "PicoW-BLE"
CHAR_UUID = "6e400002-b5a3-f393-e0a9-e50e24dcca9e"  # UART RX (write)

# Connect and get address of bt device
async def connect(DEBUG=False):
    if (DEBUG): 
        print(f"Searching for BLE device named '{DEVICE_NAME}'...")
    devices = await BleakScanner.discover(timeout=5)
    target = None
    for d in devices:
        if d.name == DEVICE_NAME:
            target = d
            break
    if not target:
        if (DEBUG):
            print(f"Device '{DEVICE_NAME}' not found.")
        return ""
    else:
        # print(f"Found {DEVICE_NAME} at address {target.address}")
        return target.address

# Send command to bt device
async def send(target_address, command, DEBUG=False):
    command = sys.argv[1].encode()
    async with BleakClient(target_address) as client:
        if (DEBUG): print(f"Connected to {DEVICE_NAME}")
        # await client.write_gatt_char(CHAR_UUID, b"LED_ON\n")
        await client.write_gatt_char(CHAR_UUID, command)
        if (DEBUG): print("Command sent.")

if len(sys.argv) != 2 or sys.argv[1] not in ("bt", "f", "b", "s"):
    print("Usage: python3 send.py [f|b|s]")
    print(sys.argv[1])

arg = sys.argv[1];
if (arg == "bt"):
    address = asyncio.run(connect())
    print(address)
else:
    arg = sys.argv[2];
    print(arg)
    asyncio.run(send(arg, arg.encode()))
