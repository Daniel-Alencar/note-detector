def calcular(v_placa, v_audio, R1, R2, RF, RG):
  print(((R1 + RF) / R1) * (RG / (RG + R2)) * v_placa - (RF / R1) * v_audio)

calcular(R1=2000, RF=10000, RG=10000, R2=110000, v_placa=5, v_audio=-0.5)