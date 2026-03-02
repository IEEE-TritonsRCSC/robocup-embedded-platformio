import math
import socket
import time

ROBOT_ID = 1
COMMAND_IP = "239.42.42.42"
COMMAND_PORT = 11000
SEND_DELAY_S = 0.1
DASH_DURATION = 2.0
TURN_DURATION = 4.0
STOP_MESSAGE = b"stop\0"
DASH_SPEED = "50.0"
TURN_SPEED = 90


def send_message(sock, message):
    sock.sendto(message, (COMMAND_IP, COMMAND_PORT))
    time.sleep(SEND_DELAY_S)


def send_stop(sock):
    send_message(sock, STOP_MESSAGE)


def build_message(action, params):
    return f"{ROBOT_ID} {action} {' '.join(params)}\0".encode()


def radians_str(degrees):
    return str(math.radians(float(degrees)))


def send_for_duration(sock, action, params, duration_s):
    message = build_message(action, params)
    end_time = time.time() + duration_s
    while time.time() < end_time:
        send_message(sock, message)


def run():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        send_for_duration(sock, "dash", [DASH_SPEED, radians_str(0)], DASH_DURATION)
        send_for_duration(sock, "dash", [DASH_SPEED, radians_str(180)], DASH_DURATION)
        send_for_duration(sock, "turn", [radians_str(TURN_SPEED)], TURN_DURATION)
        send_for_duration(sock, "turn", [radians_str(-TURN_SPEED)], TURN_DURATION)
    finally:
        send_stop(sock)
        send_stop(sock)
        sock.close()


if __name__ == "__main__":
    run()
