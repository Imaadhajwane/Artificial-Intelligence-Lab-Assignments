class Water_Jug_DFS:
    def __init__(self, jugs, goal_amount):
        self.jugs = jugs
        self.goal_amount = goal_amount
        self.visited = set()

    def get_index(self, node):
        return pow(7, node[0]) * pow(5, node[1])

    def is_goal(self, node):
        return node[0] == self.goal_amount or node[1] == self.goal_amount

    def been_there(self, node):
        return self.get_index(node) in self.visited

    def next_transitions(self, node):
        transitions = []
        a_max, b_max = self.jugs
        a, b = node

        operations = [
            # Pour first jug into second jug
            (max(0, a + b - b_max), min(a + b, b_max)),
            # Pour second jug into first jug
            (min(a + b, a_max), max(0, a + b - a_max)),
            (a_max, b),  # Fill the first jug
            (a, b_max),  # Fill the second jug
            (0, b),  # Empty the first jug
            (a, 0)  # Empty the second jug
        ]

        for op_a, op_b in operations:
            next_node = (op_a, op_b)
            if not self.been_there(next_node):
                transitions.append(next_node)
                self.visited.add(self.get_index(next_node))

        return transitions

    def dfs(self, path):
        current_node = path[-1]

        if self.is_goal(current_node):
            return path

        for next_node in self.next_transitions(current_node):
            new_path = path + [next_node]
            result = self.dfs(new_path)
            if result:
                return result

        return None

    def search(self):
        return self.dfs([(0, 0)])


def main():
    jugs = [int(input("Enter capacity of the first jug: ")),
            int(input("Enter capacity of the second jug: "))]
    goal_amount = int(input("Enter the desired amount of water In Jug 1: "))

    water_jug_dfs = Water_Jug_DFS(jugs, goal_amount)
    solution = water_jug_dfs.search()

    if solution:
        print("Actions to reach the goal state:")
        for i in range(len(solution) - 1):
            print(f"{solution[i]} -> {solution[i+1]}")
    else:
        print("No solution found.")


if __name__ == "__main__":
    main()
