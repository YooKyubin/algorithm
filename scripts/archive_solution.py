from pathlib import Path
import shutil


def main():
    script_dir = Path(__file__).resolve().parent
    project_root = script_dir.parent
    source = project_root / "main.cpp"

    if not source.is_file():
        print(f"main.cpp를 찾을 수 없습니다: {source}")
        return

    problem_name = input("문제 이름을 입력하세요: ").strip()

    if not problem_name:
        print("문제 이름이 비어 있습니다.")
        return

    problem_name = problem_name.replace(" ", "_")

    invalid_chars = '<>:"/\\|?*'
    if any(char in problem_name for char in invalid_chars):
        print(f"파일 이름에 사용할 수 없는 문자가 포함되어 있습니다: {invalid_chars}")
        return

    target = project_root / f"{problem_name}.cpp"

    if target.name.lower() == "main.cpp":
        print("main.cpp에는 저장할 수 없습니다.")
        return

    if target.exists():
        answer = input(f"{target.name} 파일이 이미 존재합니다. 덮어쓸까요? [y/N]: ").strip().lower()

        if answer != "y":
            print("작업을 취소했습니다.")
            return

    shutil.copyfile(source, target)
    print(f"저장 완료: {target.name}")


if __name__ == "__main__":
    main()
