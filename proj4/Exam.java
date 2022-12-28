package 객지프_팀플4;

import java.time.LocalDate;
import java.time.Period;

public class Exam {
	
	private String subjectName;
	private String testRange;
	private int examDate;
	private int priority;
	private int difficulty;
	private String memo;

	//getter
	public String getSubjectName() {
		return this.subjectName;
	}
	
	public String getTestRange() {
		return this.testRange;
	}
	
	public int endDate() {
		return this.examDate;
	}
	
	public int getDDay() {
		LocalDate today = LocalDate.now();
		LocalDate thisDay = LocalDate.of(2022,this.examDate/100,this.examDate%100);
		Period between = Period.between(today, thisDay);
		return between.getDays();
	}
	
	public int getPriority() {
		return this.priority;
	}
	
	public int getDifficulty() {
		return this.difficulty;
	}
	
	public String getMemo() {
		return this.memo;
	}
	
	Exam(String subject, String testRange, int examdate, int priority, int difficulty, String memo) {
		this.subjectName = subject;
		this.testRange = testRange;
		this.examDate = examdate;
		this.priority = priority;
		this.difficulty = difficulty;
		this.memo = memo;
	}

}

