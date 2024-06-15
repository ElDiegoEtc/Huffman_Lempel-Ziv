import pandas as pd
import matplotlib.pyplot as plt

# Leer los datos desde un archivo CSV
df = pd.read_csv('tiempos_totales.csv', delimiter=';')

# Convertir la columna de tiempo de ejecución a valores numéricos
df['tiempo_ejecucion'] = df['tiempo_ejecucion'].str.replace(' ns', '').astype(float)

# Separar los datos por dataset
user_id_data = df[df['dataset'] == 'huffman']
user_name_data = df[df['dataset'] == 'LZ']

# Agrupar por x y calcular el del tiempo de ejecución
user_id_avg_times = user_id_data.groupby('x')['tiempo_ejecucion'].mean()
user_name_avg_times = user_name_data.groupby('x')['tiempo_ejecucion'].mean()

# Graficar los datos
plt.figure(figsize=(10, 6))

plt.plot(user_id_avg_times.index, user_id_avg_times.values, marker='o', label=' Codificacion Huffman')
plt.plot(user_name_avg_times.index, user_name_avg_times.values, marker='x', label='Compresion Lempel-Ziv')

plt.xlabel('x')
plt.ylabel('Tiempo de ejecución (ns)')
plt.title('Tiempo de ejecución por x')
plt.grid(True)
plt.legend()

# Ajustar el rango del eje y
plt.ylim(0, user_name_avg_times.max())  # Aumentar el límite superior en un 10% del máximo valor

plt.show()
