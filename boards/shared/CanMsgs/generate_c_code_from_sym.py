"""
This file contains all the functionality required to generate C code from 
our .dbc file
"""

import logging
import os
from re import sub
from cantools.database.can.c_source import generate
from cantools.database import load_file

# We assume that the DBC file is in the same directory
# as this script
DBC_DIR = os.path.dirname(os.path.abspath(__file__))

def purge_timestamps_from_generated_code(code: str) -> str:
    """
    Purges timestamps from the generated C code so that we can diff it in CI to 
    check that the generated C code is up-to-date with the .dbc file
    """
    # Ex. replace:
    # "This file was generated by cantools version 32.4.0 Wed Jan  9 21:29:43 2019."
    # with:
    # "This file was generated by cantools"
    return sub(
        r'(This\sfile\swas\sgenerated\sby\scantools)\sversion\s\d*\.\d*\.\d*\s.*',
        r'\1', code)

def change_frame_id_capitalization(code: str) -> str:
    """
    Sets the symbol name in the FRAME_ID constant to lowercase for all CAN
    messages. This is done to allow us to reference both the constants and
    the associated function in C macros.
    """
    # Ex. replace:
    # "CANMSGS_SYMBOL1_FRAME_ID"
    # with:
    # "CANMSGS_symbol1_FRAME_ID"
    return sub(
        r'CANMSGS_(.*)_FRAME_ID',
        lambda match: r'CANMSGS_{}_FRAME_ID'.format(match.group(1).lower()),
        code)

def generate_code_from_dbc_file(database_name):
    """
    Generates C source code for the given .dbc file
    """
    database_type = 'dbc'
    dbase = load_file(database_name + '.' + database_type, database_format=database_type)

    filename_h = database_name + '.h'
    filename_c = database_name + '.c'

    header, source, _, _ = generate(
            dbase,
            database_name,
            filename_h,
            filename_c,
            "",
            floating_point_numbers=True,
            bit_fields=True
    )

    header = purge_timestamps_from_generated_code(header)
    source = purge_timestamps_from_generated_code(source)

    header = change_frame_id_capitalization(header)
    source = change_frame_id_capitalization(source)

    with open(filename_h, 'w') as fout:
        fout.write(header)

    with open(filename_c, 'w') as fout:
        fout.write(source)

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    dbc_filename = "CanMsgs"
    os.chdir(DBC_DIR)
    generate_code_from_dbc_file(dbc_filename)
