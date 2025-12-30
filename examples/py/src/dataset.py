from MANTruckDatasetPy import MANTruckDataset, Token
from utils import DATASET_PATH

if __name__ == "__main__":
    dataset_folder = str(DATASET_PATH)
    dataset_name = "v1.0-mini"
    scene_token = Token('073e6bb18188424ea9981e3845df54a6')
    dataset = MANTruckDataset(dataset_folder, dataset_name, 
                    scene_token=scene_token)