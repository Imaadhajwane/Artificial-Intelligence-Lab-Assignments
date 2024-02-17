import heapq
import random
import math

# Function to calculate the Manhattan distance heuristic


def manhattan_distance(state, goal):
    distance = 0
    for i in range(3):
        for j in range(3):
            if state[i][j] != goal[i][j] and state[i][j] != 0:
                x, y = divmod(state[i][j]-1, 3)
                distance += abs(x-i) + abs(y-j)
    return distance

# Function to print the puzzle state


def print_puzzle(state):
    for i in range(3):
        row_str = ""
        for j in range(3):
            if state[i][j] == 0:
                row_str += "   "
            else:
                row_str += " " + str(state[i][j]) + " "
            if j < 2:
                row_str += "|"
        print(row_str)
        if i < 2:
            print("---+---+---")

# Function to check if a state is the goal state


def is_goal_state(state, goal):
    return state == goal

# Function to perform hill climbing algorithm


def hill_climbing(initial_state, goal_state):
    current_state = initial_state
    current_distance = manhattan_distance(current_state, goal_state)
    visited_states = set()
    temperature = 1.0

    while True:
        print("\nCurrent State:")
        print_puzzle(current_state)
        print("Distance to goal:", current_distance)

        neighbors = []
        # Generate neighboring states
        for i in range(3):
            for j in range(3):
                if current_state[i][j] == 0:
                    for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                        ni, nj = i + dx, j + dy
                        if 0 <= ni < 3 and 0 <= nj < 3:
                            neighbor = [row[:] for row in current_state]
                            neighbor[i][j], neighbor[ni][nj] = neighbor[ni][nj], neighbor[i][j]
                            neighbors.append(neighbor)

        # Evaluate and print all neighboring states
        print("\nNeighbors:")
        for neighbor in neighbors:
            distance = manhattan_distance(neighbor, goal_state)
            print_puzzle(neighbor)
            print("Heuristic value:", distance)

        # Expand the state with the highest heuristic value
        valid_neighbors = [(manhattan_distance(neighbor, goal_state), neighbor)
                           for neighbor in neighbors
                           if tuple(map(tuple, neighbor)) not in visited_states]
        if not valid_neighbors:
            print("No valid neighbors. Local maximum reached.")
            break

        # Sort in descending order of heuristic value
        valid_neighbors.sort(reverse=True)
        next_distance, next_state = valid_neighbors[0]

        # Simulated annealing: Introduce probability of selecting a neighbor with higher heuristic value
        if next_distance <= current_distance:
            delta = current_distance - next_distance
            probability = math.exp(-delta / temperature)
            if random.random() < probability:
                current_state = next_state
                current_distance = next_distance
            else:
                print("Local maximum or plateau reached.")
                break
        else:
            current_state = next_state
            current_distance = next_distance

        visited_states.add(tuple(map(tuple, current_state)))
        temperature *= 0.95  # Reduce the temperature for each iteration

    # print("\nFinal State Reached:")
    # print_puzzle(current_state)
    # print("Distance to goal:", current_distance)

# Function to take input for the puzzle state


def input_state():
    state = []
    for _ in range(3):
        row = list(map(int, input().split()))
        state.append(row)
    return state

# Main function


def main():
    print("Enter the initial state of the puzzle (use 0 for empty space):")
    initial_state = input_state()

    print("Enter the goal state of the puzzle:")
    goal_state = input_state()

    hill_climbing(initial_state, goal_state)


if __name__ == "__main__":
    main()
