import gym
import numpy as np
from time import sleep
import random

env = gym.make("FrozenLake8x8-v1").env
qtable = np.zeros([env.observation_space.n, env.action_space.n])

alpha = 0.1
gamma = 0.95
epsilon = 0.4

for i in range(5000):
    state = env.reset()[0]

    done = False
    while not done:
        if random.uniform(0, 1) < epsilon:
            action = env.action_space.sample()

        else:
            action = np.argmax(qtable[state])

        new_state, reward, done, info, _ = env.step(action)

        if done and reward != 1:
            reward = -10

        elif reward == 0:
            reward = -0.5

        else:
            reward = 20

        qtable[state, action] = qtable[state, action] + alpha * \
            (reward + gamma *
                np.max(qtable[new_state, :])-qtable[state, action])

        state = new_state

env.reset()

result = []
steps = 0
done = False

while not done:
    action = np.argmax(qtable[state])
    state, reward, done, info, _ = env.step(action)

    result.append({
        # 'frame': env.render(),
        'state': state,
        'action': action,
        'reward': reward,
        'done': done
    }
    )
    steps += 1

print("Solved in {} steps.".format(steps))
sleep(5)

for element in result:
    print(element)

print(qtable)
