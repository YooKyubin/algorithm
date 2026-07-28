import json
import sys


def main():
    text = input().strip()

    if not text:
        print("JSON input is required.", file=sys.stderr)
        return

    try:
        matrix = json.loads(text)
    except json.JSONDecodeError as error:
        print(f"Invalid JSON: {error}", file=sys.stderr)
        return

    if not isinstance(matrix, list):
        print("A JSON array is required.", file=sys.stderr)
        return

    if not matrix:
        print()
        return

    if all(isinstance(item, list) for item in matrix):
        rows = matrix
    elif all(not isinstance(item, list) for item in matrix):
        rows = [matrix]
    else:
        print("Do not mix arrays and values in the same array.", file=sys.stderr)
        return

    for row in rows:
        cells = (json.dumps(cell, ensure_ascii=False) for cell in row)
        print(" ".join(cells))


if __name__ == "__main__":
    main()
