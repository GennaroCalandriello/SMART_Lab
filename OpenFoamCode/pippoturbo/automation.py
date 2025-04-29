#!/usr/bin/env python3
import os
import re
import subprocess
import argparse #argparse: costruisce un’interfaccia a riga di comando per passare opzioni e argomenti.
import sys
from PyFoam.RunDictionary.ParsedParameterFile import ParsedParameterFile
import shutil

def modify_dict(dict_path, modifications):
    """
    Apporta modifiche a un file di dizionario OpenFOAM.
    `modifications` è un dict {parametro: nuovo_valore}.
    """
    with open(dict_path, 'r') as f:
        lines = f.readlines()

    # Costruisce una regex che “cattura” linee che cominciano con uno dei parametri
    pattern = re.compile(
        r'^\s*({})\s+(\S+)(.*);'
        .format('|'.join(map(re.escape, modifications.keys())))
    )

    with open(dict_path, 'w') as f:
        for line in lines:
            m = pattern.match(line)
            if m:
                key     = m.group(1)             # nome del parametro trovato
                new_val = modifications[key]     # nuovo valore da inserire
                # ricompone la riga sostituendo la vecchia occorrenza con new_val
                line = f"{key}    {new_val}{m.group(3)};\n"
            f.write(line)


def run_commands(case_dir, commands):
    """Esegue una lista di comandi shell nella directory del caso."""
    for cmd in commands:
        print(f"Running: {' '.join(cmd)}")
        subprocess.run(cmd, cwd=case_dir, check=True)

def main():
    # Prende tutti gli argomenti dopo il nome dello script
    # per passarli direttamente a foamListTimes
    # args = sys.argv[1:]
    # if not args:
    #     print("Uso: foamListTimes.py [options]")
    #     print("Esempio: foamListTimes.py -rm 0.1 0.2")
    #     sys.exit(1)

    cmd = ["foamListTimes", "-rm"]
    
    # Esegue il comando e ferma lo script se fallisce
    # subprocess.run(cmd, check=True)
    # cmd1 = ["ideasUnvToFoam", "meshtry.unv"]
    cmd1 = ["rm -rf proc*"]
    
    cmd2 = ["checkMesh"]
    cmd3 = ["simpleFoam"]
    cmd4 = ["paraFoam"]
    cmd5 =["decomposePar"]
    cmd6 = ["mpirun", "-np", "6", "simpleFoam", "-parallel"]
    cmd7 = ["reconstructPar"]

    # CALCELLA I FILES
    print("Eseguo:", " ".join(cmd))
    subprocess.run(cmd, check=True)
    print("Eseguo:", " ".join(cmd1))
    subprocess.run(cmd1, shell=True, check=True)
    
    comm = input("Vuoi continuare? (y/n): ")
    if comm.lower() != 'y':
        print("Operazione annullata.")
        return
    else:
        print("Continuo...")
    #
        # DA QUI IN POI PER LA SIMULAZIONE
        print("Eseguo:", " ".join(cmd2))
        subprocess.run(cmd2, check=True)
        print("Eseguo:", " ".join(cmd3))
        subprocess.run(cmd5, check=True)
        print("Eseguo:", " ".join(cmd4))
        subprocess.run(cmd6, check=True)
        print("Eseguo:", " ".join(cmd7))
        subprocess.run(cmd7, check=True)
        print("Eseguo:", " ".join(cmd4))
        subprocess.run(cmd4, check=True)

         # === sposta le cartelle dei time-step in results/ ===
        case_dir = os.getcwd()  # o la variabile che usi per la cartella del case
        results_dir = os.path.join(case_dir, "results")
        os.makedirs(results_dir, exist_ok=True)

        # scorri tutte le sottocartelle nel case
        for name in os.listdir(case_dir):
            full = os.path.join(case_dir, name)
            # è una cartella numerica diversa da '0'?
            if os.path.isdir(full) and name != "0":
                print(f"Spostando {name} → results/{name}")
                shutil.move(full, os.path.join(results_dir, name))

        print("Tutti i time-step sono stati spostati in 'results/'")

def dictMod():
    """
    Opens system/controlDict in the given case directory,
    sets the value of deltaT to new_deltaT, and saves the file.
    
    :param case_dir: Path to the root of the OpenFOAM case
    :param new_deltaT: New time step (float or string, e.g. 0.005 or "1e-3")
    """
    # Build path to controlDict
    new_deltaT = "0.1"  # Example new deltaT value
    case_dir =""
    control_dict_path = f"{case_dir}system/controlDict"
    
    # Load and parse controlDict
    control = ParsedParameterFile(control_dict_path)
    
    # Show old value (for debug)
    old = control["deltaT"]
    print(f"Old deltaT = {old}")
    
    # Imposta il nuovo deltaT
    control["deltaT"] = new_deltaT
    control["endTime"] = 40
    control["writeInterval"] = 5
    
    # Salva il file
    control.writeFile()
    print(f"Updated deltaT to {new_deltaT} in system/controlDict")
    print(f"Updated endTime to {control['endTime']} in system/controlDict")


if __name__ == "__main__":
    dictMod()
    main()
   
    