import math
import socket
import time

ROBOT_ID = 1
COMMAND_IP = "239.42.42.42"
COMMAND_PORT = 11000
SEND_DELAY_S = 0.5
STOP_MESSAGE = b"stop\0"

SHORT_TO_LONG = {
    "t": "turn",
    "d": "dash",
    "s": "skick",
    "k": "kick",
    "c": "catch",
}

HELP_TEXT = """The commands are as follows:
  t <angle>       -> turn to angle (in degrees/second)
  d <speed> <dir> -> dash with speed in direction (dir in degrees between -180 and 180)
  s <power>       -> skick (dribbler pulse; power ignored by STM32)
  k               -> kick
  c               -> catch
  stop            -> stop all motors
"""


def print_help():
    print(HELP_TEXT)


def normalize_command(command):
    return command.strip()


def is_quit(command):
    return command.lower() == "q"


def is_stop(command):
    return command.lower() == "stop"


def first_char(command):
    return command[0].lower() if command else ""


def parse_floats(values):
    return [str(float(value)) for value in values]


def get_params(command, n_params):
    try:
        params = command.split()[1 : 1 + n_params]
        if len(params) != n_params:
            raise ValueError
        return parse_floats(params)
    except ValueError:
        print(f"Invalid command. Please enter {n_params} parameters.")
        return None


def to_radians(value):
    return str(math.radians(float(value)))


def update_params_for_turn(params):
    params[0] = to_radians(params[0])
    return params


def update_params_for_dash(params):
    params[1] = to_radians(params[1])
    return params


def parse_action_and_params(command):
    leading = first_char(command)
    if leading == "t":
        params = get_params(command, 1)
        return (SHORT_TO_LONG[leading], update_params_for_turn(params)) if params else None
    if leading == "d":
        params = get_params(command, 2)
        return (SHORT_TO_LONG[leading], update_params_for_dash(params)) if params else None
    if leading == "s":
        params = get_params(command, 1)
        return (SHORT_TO_LONG[leading], params) if params else None
    if leading in {"k", "c"}:
        return (SHORT_TO_LONG[leading], [])

    print("Unknown command. Please try again.")
    return None


def parse_command(command):
    normalized = normalize_command(command)
    if not normalized:
        return None
    if is_stop(normalized):
        return ("stop", [])
    return parse_action_and_params(normalized)


def send_message(sock, message):
    sock.sendto(message, (COMMAND_IP, COMMAND_PORT))
    time.sleep(SEND_DELAY_S)


def send_stop(sock):
    send_message(sock, STOP_MESSAGE)


def build_message(action, params):
    return f"{ROBOT_ID} {action} {' '.join(params)}\0".encode()


def run():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    print_help()

    try:
        while True:
            command = input("Enter command (or 'q' to quit): ")
            if is_quit(command):
                raise KeyboardInterrupt

            parsed = parse_command(command)
            if parsed is None:
                continue

            action, params = parsed
            if action == "stop":
                send_stop(sock)
                continue

            message = build_message(action, params)
            send_message(sock, message)
    except KeyboardInterrupt:
        print("\nSending stop command and exiting...")
        send_stop(sock)
        send_stop(sock)
        sock.close()
        print("Done.")


if __name__ == "__main__":
    run()
