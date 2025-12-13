from MANTruckDatasetPy import Sample, SampleSequence
from utils import SAMPLE_FILE

if __name__ == "__main__":
  sample_mgr = SampleSequence()
  sample_mgr.read_samples(str(SAMPLE_FILE), "073e6bb18188424ea9981e3845df54a6")
  for sample in sample_mgr:
    print(f"Sample token: {sample.get_token()}, Timestamp: {sample.get_timestamp()}")