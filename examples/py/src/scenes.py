from MANTruckDataset import Scene, SceneManager
from utils import DATASET_PATH, SCENE_FILE

if __name__ == "__main__":
  scene_mgr = SceneManager()
  scene_mgr.read_scenes(str(SCENE_FILE))

  for key, scene in scene_mgr:
    print(f"Scene token: {scene.get_token()}, Description: {scene.get_description()}")