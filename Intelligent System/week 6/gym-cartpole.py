from time import sleep
import gym
import random
import warnings
warnings.filterwarnings("ignore", category=DeprecationWarning)


env_name = "Acrobot-v1"
env = gym.make(env_name)
print("Observation space:", env.observation_space.high)
print("Action space:", env.action_space.n)


# class Agent():
#     def __init__(self, env):
#         self.action_size = env.action_space.n
#         print("Action size:", self.action_size)

#     def get_action(self, state):
#         action = random.choice(range(self.action_size))
#         pole_angle = state[2]
#         # 0 Push cart to the left #1 Push cart to the right
#         action = 0 if pole_angle < 0 else 1
#         return action


# agent = Agent(env)
# state = env.reset()[0]
# print(state)
# action = env.action_space.sample()
# print(action)

# for _ in range(100):
#     # action = env.action_space.sample()
#     action = agent.get_action(state)
#     state, reward, done, _, _ = env.step(action)
#     print(reward, state, done)
#     env.render()
#     if reward < 1:
#         sleep(3)
#         break
# env.close()
