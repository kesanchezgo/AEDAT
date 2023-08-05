if len(times) >= 2:
            avg_time = statistics.mean(times)
            std_dev = statistics.stdev(times)
        else:
            avg_time = times[0] if times else 0
            std_dev = 0