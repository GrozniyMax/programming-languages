import subprocess

test_cases = {
    "very_long": "qwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwertyqwerty",
    "test": "test word of dictionary",
    "empty": "",
    "russian": "Русский текст",
    "normal": "Typicall word that are expected to be stored in dictionary",
    "first": "first word of dictionary",
    "qwerty": "Not found",
    "normal word": "Typicall word that are expected to be stored in dictionary"
}

exit_code = 0

for input, expected_output in test_cases.items():

    result = subprocess.run(
        ["./main"],
        input=input.encode("utf-8"),
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )
    actual_output = result.stdout.decode("utf-8")
    # its okay
    # actual_output = actual_output.replace("Enter a word to found: ", "")

    if ("Enter a word to found: " not in actual_output):
        print("Test failed: No input prompt found")
        exit_code = 1
    if ("\n" not in actual_output):
        print("Test failed: No newline found")
        exit_code = 1
    actual_output = (actual_output.replace("\n", "", 1)
                     .replace("Enter a word to found: ", "", 1))

    if (expected_output != actual_output):
        print(fr'Test with input: "{input} failed. Test returned: {actual_output} instead of {expected_output}')
        exit_code = 1
else:
    print("Tests passed")

exit(exit_code)
