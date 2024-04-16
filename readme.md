# CalTrain (Synchronization and Mutual Exclusion)

This assignment is based on assignment0 offered at Stanford CS140 Operating Systems.

## Usage

To compile the code, use the following command:

```bash
make
```

Once compiled, you can run the simulation using the provided script(it executes the shell script):

```bash
./repeat.sh
```

## Output and Error Handling

The output of the simulation will be printed in [final_result.out](final_result.out/).

Any errors encountered during execution will be printed in the terminal.

## Cleaning Up Compiled Code

To delete the compiled code or any generated files produced during the compilation process, you can use the following command:

```bash
make clean
```

If you encounter any permission errors or other issues during execution, Ask ChatGPT for guidance. 😄

## Structure

The simulation consists of the following files:

- `caltrain.c`: Contains the function implementations for the train station simulation, .
- `caltrain.h`: Header file defining the station struct and function prototypes used in the simulation.

**Note:** The code is implemented twice in [caltrain.c](caltrain.c/), with one version using two variables and the other using three variables. Both versions are included in the same file, with one commented out and the other active. To run a specific version, comment out the other and uncomment the desired one.

## Functionality

The simulation includes the following functionalities:

- **station_init**: Initializes the train station, including mutex and condition variables.
- **station_load_train**: Simulates the arrival of a train and manages the boarding process of passengers onto the train.
- **station_wait_for_train**: Simulates a passenger waiting for a train to arrive and board.
- **station_on_board**: Simulates a passenger boarding the train.

## Implementation Details

- **Mutex and Condition Variables**: The simulation uses mutex locks and condition variables to ensure thread safety and synchronization between passengers and trains.
- **Synchronization**: Passengers wait for trains to arrive, and trains wait for passengers to board before departing.

