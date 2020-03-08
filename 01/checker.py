from subprocess import Popen, PIPE, STDOUT, TimeoutExpired

def run(command, process_input):
    process = Popen(command, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT)

    try:
        out = process.communicate(input=process_input, timeout=10)[0]
    except TimeoutExpired:
        process.kill()
        return (1, '')

    code = process.wait()
    return code, out

def test(command, process_input, expected_code):
    code, out = run(command, process_input) #allocating 20 bytes of memory

    if (code != expected_code):
        print('expected return value ', expected_code, ', got ', code, sep='')
        return

    out = out.decode('ascii').replace('\r', '')

    try:
        out = list(map(int, out.split('\n')[:-1]))
    except:
        print('invalid output')
        return

    first_alloc = out[0]

    if (first_alloc == 0): #10 bytes alloc; should be fine
        print('wrong_answer 1')
        return

    second_alloc = out[1]

    if (second_alloc == 0 or second_alloc - first_alloc != 10): #10 bytes alloc; should be fine
        print('wrong_answer 2')
        return

    failed_alloc = out[2]

    if (failed_alloc != 0): #1 byte alloc; shouldn't fit
        print('wrong_answer 3')
        return

    fourt_alloc = out[3]

    if (fourt_alloc != first_alloc): #first alloc after reset; should be fine
        print('wrong_answer 4')
        return

    fifth_alloc = out[4]

    if (fifth_alloc != 0): #this shouldn't fit by 1
        print('wrong_answer 5')
        return

    sixth_alloc = out[5]

    if (sixth_alloc == 0 or sixth_alloc - fourt_alloc != 1): #allocating the rest of the memory
        print('wrong_answer 6')
        return

    print('test passed')

test('./main',  b'''MAKE_ALLOCATOR 20
                    ALLOCATE 10
                    ALLOCATE 10
                    ALLOCATE 1
                    RESET
                    ALLOCATE 1
                    ALLOCATE 20
                    ALLOCATE 19
                    EXIT''', 0)
