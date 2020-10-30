import subprocess
from subprocess import check_call, check_output
import os
import re

class BColors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def HasTimeout():
    cmd = 'timeout 0 echo'
    try: 
        check_output(cmd, shell=True, stderr=subprocess.STDOUT)
        return True
    except subprocess.CalledProcessError as e:
        return False

def ProcessOutput(output):
    matches = re.findall('Will run test at index ([0-9]+).*\n', output)
    assert(len(matches) > 0)
    last_index = matches[-1]
    return last_index, len(matches)

def RunCommand(cmd, timeout_sec=20):
    '''Runs a shell command with timeout.'''

    timeout_blurb = 'timeout {}'.format(timeout_sec) if HasTimeout() else ''
    cmd_with_timeout = '{} {}'.format(timeout_blurb, cmd)
    try:
        output = check_output(cmd_with_timeout, shell=True,
                              stderr=subprocess.STDOUT)
        return (True, output)
    except subprocess.CalledProcessError as e:
        return (False, e.output)

def GetTestCommand(test_type, test_file, extra_switch):
    return './lzw_test --type {} --file {} {}'.format(test_type, test_file, extra_switch)

def PrintRepeatCommand(test_file, last_test_index, type_switch, invalid_input_switch):
    print '\tto repeat only last test run ./lzw_test --file {} --test_index {} {} {}'.format(test_file, last_test_index, type_switch, invalid_input_switch)
    print '\tto extract input for last test run ./lzw_test --file {} --test_index {} {} {} --dump'.format(test_file, last_test_index, type_switch, invalid_input_switch)


def TestAndPrintStatus(prefix, test_type, test_file, expected_count, check_invalid_input=False):
    invalid_input_switch = ''
    if check_invalid_input:
        invalid_input_switch = '--invalid_input'

    cmd = GetTestCommand(test_type, test_file, invalid_input_switch)
    ok, output = RunCommand(cmd)
    last_test_index, tests_run = ProcessOutput(output)
    
    prefix = 'testing {} for '.format(test_type) + prefix

    type_switch = ''
    if test_type == 'encode' or test_type == 'decode':
        type_switch = '--type {}'.format(test_type)

    res = 0
    if ok and tests_run == expected_count:
        print '{}: {}OK{}'.format(prefix, BColors.OKGREEN, BColors.ENDC)
        res = 1
    elif ok:
        print '{}: {}FAILED{} not all tests completed'.format(prefix, BColors.FAIL, BColors.ENDC)
        PrintRepeatCommand(test_file, last_test_index, type_switch, invalid_input_switch)
    else:
        print '{}: {}FAILED{}'.format(prefix, BColors.FAIL, BColors.ENDC)
        PrintRepeatCommand(test_file, last_test_index, type_switch, invalid_input_switch)
        
    return res

if __name__ == "__main__":
    oks = 0
    first_grp_size = 6
    print 'Test group one (all possible sequences with N elements):'
    for i in range(first_grp_size):
        num_seq = 4 ** (i + 1)
        prefix = '{} sequences of size {}'.format(num_seq, i + 1)
        oks += TestAndPrintStatus(prefix, 'encode',
                                  '../test_data/all_bases_{}'.format(i + 1),
                                  num_seq)
        oks += TestAndPrintStatus(prefix, 'decode',
                                  '../test_data/all_bases_{}'.format(i + 1),
                                  num_seq)
    print 'Group one score: {}/{}\n'.format(oks, first_grp_size * 2)

    oks = 0
    second_grp_size = 8
    print 'Test group two (pre-generated random sequences of size N):'
    for i in range(second_grp_size):
        prefix = 'sequence of size {}'.format(1 << (2 * (i)))
        oks += TestAndPrintStatus(prefix, 'encode',
                                  '../test_data/rnd_{}'.format(i), 1)
        oks += TestAndPrintStatus(prefix, 'decode',
                                  '../test_data/rnd_{}'.format(i), 1)
    print 'Group two score: {}/{}\n'.format(oks, second_grp_size * 2)

    oks = 0
    print 'Test group three (invalid inputs):'
    prefix = 'invalid encoder inputs'
    oks += TestAndPrintStatus(prefix, 'encode',
                              '../test_data/invalid_encoder_inputs', 2,
                              True)
    prefix = 'invalid decoder inputs'
    oks += TestAndPrintStatus(prefix, 'decode',
                              '../test_data/invalid_decoder_inputs', 4,
                              True)
    print 'Group three score: {}/{}\n'.format(oks, 2)
