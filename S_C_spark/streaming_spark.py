from pyspark.sql import SparkSession
from pyspark.sql.functions import col, to_timestamp, window

# Crear sesión de Spark
spark = SparkSession.builder \
    .appName("StructuredStreamingChat") \
    .getOrCreate()

# Leer los datos del socket (puerto 9999)
lines = spark.readStream \
    .format("socket") \
    .option("host", "localhost") \
    .option("port", 9999) \
    .load()

# Convertir las líneas en timestamps
timestamps = lines.select(to_timestamp(col("value"), "yyyy-MM-dd HH:mm:ss").alias("timestamp"))

# Contar el número de eventos por minuto
events_per_minute = timestamps \
    .withWatermark("timestamp", "1 minute") \
    .groupBy(window(col("timestamp"), "1 minute")) \
    .count()

# Iniciar la consulta en consola
query = events_per_minute \
    .writeStream \
    .outputMode("append") \
    .format("console") \
    .start()

# Mantener la ejecución
query.awaitTermination()
