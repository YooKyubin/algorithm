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

    if matrix and all(isinstance(item, list) for item in matrix):
        rows = matrix
        column_count = len(rows[0]) if rows else 0

        if not all(len(row) == column_count for row in rows):
            print("All rows must have the same length.", file=sys.stderr)
            return

        print(len(rows), column_count)
    elif all(isinstance(item, str) for item in matrix):
        rows = [[item] for item in matrix]
        print(len(rows))
    elif all(not isinstance(item, list) for item in matrix):
        rows = [matrix]
        print(len(matrix))
    else:
        print("Do not mix arrays and values in the same array.", file=sys.stderr)
        return

    for row in rows:
        cells = (
            cell if isinstance(cell, str) else json.dumps(cell, ensure_ascii=False)
            for cell in row
        )
        print(" ".join(cells))


if __name__ == "__main__":
    main()
