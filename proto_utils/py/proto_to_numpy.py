import numpy as np
from eigen_pb2 import EigenMatrix, EigenVector


def to_numpy(obj):
    """
    Converts a EigenMatrix or EigenVector message (proto) to its numpy
    equivalent
    """
    if isinstance(obj, EigenMatrix):
        out = np.array(obj.data).reshape(obj.rows, obj.cols, order="F")
    elif isinstance(obj, EigenVector):
        out = np.array(obj.data)
    else:
        raise ValueError("incorrect object type")

    return out