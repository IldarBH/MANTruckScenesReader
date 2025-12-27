from MANTruckDatasetPy import Sample, SampleSequence, Token
from utils import SAMPLE_FILE

if __name__ == "__main__":
  sample_mgr = SampleSequence()
  sample_mgr.read_samples(str(SAMPLE_FILE), Token("073e6bb18188424ea9981e3845df54a6"))
  for sample in sample_mgr:
    print(f"Sample token: {sample.get_token().value}, Timestamp: {sample.get_timestamp()}")