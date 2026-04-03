import serial
import time
from telegram.ext import Updater, CommandHandler

# 🔴 CHANGE THESE
BOT_TOKEN = "paste telegram token"
COM_PORT = "COM4"        # Windows: COM3 | Linux/Mac: /dev/ttyUSB0
BAUD_RATE = 9600

ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
time.sleep(2)

latest_data = None

def read_arduino():
    global latest_data

    # 🔥 Read all buffered lines and keep only the latest
    while ser.in_waiting > 0:
        line = ser.readline().decode(errors="ignore").strip()
        if line.startswith("DATA:"):
            latest_data = line

def start(update, context):
    update.message.reply_text(
        "🌱 Smart Irrigation Bot Started\n"
        "Use /status to get live soil data"
    )

def status(update, context):
    read_arduino()

    if latest_data:
        raw, moisture, soil, pump = latest_data.replace("DATA:", "").split(",")

        message = (
            "🌱 Soil Monitoring Status\n\n"
            f"🔢 Soil Raw Value : {raw}\n"
            f"💧 Moisture Level : {moisture}%\n"
            f"🌍 Soil Status   : {soil}\n"
            f"🚰 Pump Status   : {pump}"
        )
    else:
        message = "⚠️ Waiting for data from Arduino..."

    update.message.reply_text(message)

def main():
    updater = Updater(BOT_TOKEN, use_context=True)
    dp = updater.dispatcher

    dp.add_handler(CommandHandler("start", start))
    dp.add_handler(CommandHandler("status", status))

    updater.start_polling()
    updater.idle()

if __name__ == "__main__":
    main()
