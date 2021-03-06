#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 21 13:34:32 2018
# quality metrics
@authors: Daniil Kazantsev, Edoardo Pasca
"""
import numpy as np

def nrmse(im1, im2):
    rmse = np.sqrt(np.sum((im2 - im1) ** 2) / float(im1.size))
    max_val = max(np.max(im1), np.max(im2))
    min_val = min(np.min(im1), np.min(im2))
    return 1 - (rmse / (max_val - min_val))
    
def rmse(im1, im2):
    rmse = np.sqrt(np.sum((im1 - im2) ** 2) / float(im1.size))
    return rmse
