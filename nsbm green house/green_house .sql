-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Apr 22, 2023 at 06:28 PM
-- Server version: 10.4.25-MariaDB
-- PHP Version: 8.1.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `green_house`
--

-- --------------------------------------------------------

--
-- Table structure for table `sensordatahistory`
--

CREATE TABLE `sensordatahistory` (
  `id` int(6) UNSIGNED NOT NULL,
  `Pressure` varchar(30) DEFAULT NULL,
  `Water_Temperature` varchar(30) DEFAULT NULL,
  `Humidity` varchar(30) DEFAULT NULL,
  `Temperature` varchar(30) DEFAULT NULL,
  `Soil` varchar(30) DEFAULT NULL,
  `Pump_status` varchar(30) DEFAULT NULL,
  `Mist_status` varchar(30) DEFAULT NULL,
  `Door_status` varchar(30) DEFAULT NULL,
  `reading_time` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `sensordatahistory`
--

INSERT INTO `sensordatahistory` (`id`, `Pressure`, `Water_Temperature`, `Humidity`, `Temperature`, `Soil`, `Pump_status`, `Mist_status`, `Door_status`, `reading_time`) VALUES
(1, '2', '30', '80', '32', '50%', 'ON', 'ON', 'CLOSE', '2023-04-22 07:23:33');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `sensordatahistory`
--
ALTER TABLE `sensordatahistory`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `sensordatahistory`
--
ALTER TABLE `sensordatahistory`
  MODIFY `id` int(6) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
