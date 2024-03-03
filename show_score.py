import json

with open('numbers.json', 'r') as f:
    numbers = json.load(f)

screen = [[0 for _ in range(12)] for _ in range(8)]


def print_numbers(scr):
    for r in scr:
        row = ''
        for i, c in enumerate(r):
            if i % 5 == 0:
                row += '    '
            if c == 0:
                row += ' '
            else:
                row += '0'
        print(row)

def print_screen(scr):
    for r in scr:
        row = ''
        for c in r:
            if c == 0:
                row += ' '
            else:
                row += '0'
        print(row)


def get_right_number(num: int):
    num1 = num // 10
    num2 = num % 10
    num1_start_x = 5
    num1_start_y = 7

    num2_start_x = 0
    num2_start_y = 7
    # First number
    for screen_y, number_y in zip(range(num1_start_y, num1_start_y+5), range(num1*5, num1*5 + 5)):
        for screen_x, number_x in zip(range(num1_start_x, num1_start_x+3), range(3)):
            screen[screen_x][screen_y] = numbers[number_x][number_y]

    # Second number
    for screen_y, number_y in zip(range(num2_start_y, num2_start_y+5), range(num2*5, num2*5 + 5)):
        for screen_x, number_x in zip(range(num2_start_x, num2_start_x+3), range(3)):
            screen[screen_x][screen_y] = numbers[number_x][number_y]


def rotate_180():
    rotated = [[0 for _ in range(50)] for _ in range(3)]
    for original_x, rotated_x in zip(range(50), range(49, -1, -1)):
        for original_y, rotated_y in zip(range(3), range(2, -1, -1)):
            rotated[rotated_y][rotated_x] = numbers[original_y][original_x]
    return rotated


def get_left_number(num: int):
    numbers = rotate_180()
    num1 = num // 10
    num2 = num % 10
    num1_start_x = 0
    num1_start_y = 0

    num2_start_x = 5
    num2_start_y = 0
    # First number
    for screen_y, number_y in zip(range(num1_start_y, num1_start_y+5), range((9-num1)*5, (9-num1)*5 + 5)):
        for screen_x, number_x in zip(range(num1_start_x, num1_start_x+3), range(3)):
            screen[screen_x][screen_y] = numbers[number_x][number_y]

    # Second number
    for screen_y, number_y in zip(range(num2_start_y, num2_start_y+5), range((9-num2)*5, (9-num2)*5 + 5)):
        for screen_x, number_x in zip(range(num2_start_x, num2_start_x+3), range(3)):
            screen[screen_x][screen_y] = numbers[number_x][number_y]


print_numbers(numbers)
print('\n\n')
print_numbers(rotate_180())
print('\n\n')

get_right_number(14)
get_left_number(37)
print_screen(screen)