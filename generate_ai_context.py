import os
import subprocess
import sys


def consolidate_code_for_ai(root_dir, output_filepath):
    # Notice I added '.plecs' to this list!
    allowed_extensions = {'.c', '.h', '.cpp', '.hpp', '.cla', '.cmd', '.plecs', '.txt'}

    ignored_dirs = {'.git', '.settings', '.theia', '.clangd', 'Debug', 'Release'}

    with open(output_filepath, 'w', encoding='utf-8') as outfile:
        for dirpath, dirnames, filenames in os.walk(root_dir):
            dirnames[:] = [d for d in dirnames if d not in ignored_dirs]

            for filename in filenames:
                ext = os.path.splitext(filename)[1].lower()

                # Exclude specific text files we don't want if we included .txt broadly
                if ext == '.txt' and "readme" not in filename.lower() and "log" not in filename.lower():
                    continue  # Only keep specific useful text files like logs or readmes

                if ext in allowed_extensions:
                    filepath = os.path.join(dirpath, filename)
                    rel_path = os.path.relpath(filepath, root_dir)

                    outfile.write(f"\n{'=' * 80}\n")
                    outfile.write(f"File: {rel_path}\n")
                    outfile.write(f"{'=' * 80}\n\n")

                    try:
                        with open(filepath, 'r', encoding='utf-8') as infile:
                            outfile.write(infile.read())
                    except UnicodeDecodeError:
                        try:
                            with open(filepath, 'r', encoding='latin-1') as infile:
                                outfile.write(infile.read())
                        except Exception as e:
                            outfile.write(f"// Error reading file: {e}\n")
                    except Exception as e:
                        outfile.write(f"// Error reading file: {e}\n")

                    outfile.write("\n\n")


def open_file_explorer(path):
    """Cross-platform function to open the file explorer."""
    print(f"Opening folder: {path}")
    try:
        if sys.platform == "win32":
            os.startfile(path)
        elif sys.platform == "darwin":  # macOS
            subprocess.call(["open", path])
        else:  # Linux
            subprocess.call(["xdg-open", path])
    except Exception as e:
        print(f"Could not automatically open folder: {e}")


if __name__ == "__main__":
    project_root = "."

    # 1. Calculate the parent directory (one level up)
    parent_dir = os.path.abspath(os.path.join(project_root, os.pardir))

    # 2. Define the exact path for the output file
    output_filename = "ai_project_context.txt"
    output_filepath = os.path.join(parent_dir, output_filename)

    print(f"Scanning project in: {os.path.abspath(project_root)}")
    consolidate_code_for_ai(project_root, output_filepath)
    print(f"Done! File saved to: {output_filepath}")

    # 3. Auto-open the folder
    open_file_explorer(parent_dir)