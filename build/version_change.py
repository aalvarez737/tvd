#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import sys
import os
from argparse import ArgumentParser

from subprocess import Popen, STDOUT, PIPE
try:
	from urllib import unquote
except: #python 3
	from urllib.parse import unquote
import re
try:
	import json #for reading logs
except:
	import simplejson as json


class GitException(Exception):
	"""Exception class allowing a exit_code parameter and member
	to be used when calling Git to return exit code"""
	def __init__(self, msg, exit_code=None):
		super(GitException, self).__init__(msg)
		self.exit_code = exit_code
		

class Revision(object):
	"""A representation of a revision.
	Available fields are::

	  node, rev, author, branch, parents, date, tags, desc

	A Revision object is equal to any other object with the same value for node
	"""
	def __init__(self, json_log):
		"""Create a Revision object from a JSON representation"""
		rev = json.loads(json_log)
		
		for key in rev.keys():
			self.__setattr__(key, unquote(rev[key]))

		if not self.parents:
			self.parents = []
		else:
			self.parents = self.parents.split()

	def __eq__(self, other):
		"""Returns true if self.node == other.node"""
		return self.node == other.node


class Repo(object):
	"""A representation of a Mercurial repository"""
	def __init__(self, path, user=None):
		"""Create a Repo object from the repository at path"""
		self.path = path
		self.cfg = False
		self.user = user

	def __getitem__(self, rev):
		"""Get a Revision object for the revision identifed by rev"""
		return self.revision(rev)

	@classmethod
	def command(cls, path, *args):
		"""Run a git command in path and return the result. Throws on error."""
		if not path:
			path = '.'
		proc = Popen(["git"] + list(args), stdout=PIPE, stderr=PIPE, cwd=path)

		out, err = [x.decode("utf-8") for x in proc.communicate()]

		if proc.returncode:
			cmd = "git " + " ".join(args)
			raise GitException("Error running %s:\n\tErr: %s\n\tOut: %s\n\tExit: %s" 
							% (cmd,err,out,proc.returncode), exit_code=proc.returncode)
		return out

	def git_command(self, *args):
		"""Run a git command on this repo and return the result.
		Throws on error."""
		return Repo.command(self.path, *args)

	def git_init(self):
		"""Initialize a new repo"""
		self.git_command("init")

	def git_id(self):
		"""Get the output of the git id command (truncated node)"""
		res = self.git_command("log","--pretty=format:%H", "-n", "1")
		return res.strip("\n +")
		
	def git_add(self, filepath):
		"""Add a file to the repo"""
		self.git_command("add", filepath)

	def git_remove(self, filepath):
		"""Remove a file from the repo"""
		self.git_command("rm", filepath)

	def git_checkout(self, reference, clean=False):
		"""Update to the revision indetified by reference"""
		cmd = ["checkout", str(reference)]
		self.git_command(*cmd)

	def git_branches(self):
		"""Gets a list with the names of all branches"""
		res = self.git_command("branch")
		return [head.strip(" *") for head in res.split("\n") if head]

	def git_branch(self, name, start="HEAD"):
		"""Create the branch named 'name'"""
		return self.git_command("branch", name, start)

	def git_tags(self, pattern=None, points_at=None, **kwargs):
		"""Get repository tags"""
		args = []
		for key in kwargs:
			args.extend([key, kwargs[key]])
		if points_at:
			args.extend(['--points-at', points_at])
		if pattern:
			args.append(pattern)
		res = self.git_command("tag", "-l", *args)
		return [tag for tag in res.split("\n") if tag]

	def git_tag(self, name, **kwargs):
		"""Create the tag named 'name'"""
		args = []
		for key in kwargs:
			args.extend(["-%s" % key, kwargs[key]])
		return self.git_command("tag", name, *args)

	def git_merge(self, reference):
		"""Merge reference to current"""
		self.git_command("merge", reference)
		
	def git_reset(self, hard=True, *files):
		"""Revert repository"""
		
		hard = ["--hard"] if hard else []
		cmd = ["reset"] + hard + list(files)
		self.git_command(*cmd)

	def git_node(self):
		"""Get the full node id of the current revision"""
		res = self.git_command("log", "-r", self.git_id(), "--template", "{node}")
		return res.strip()

	def git_commit(self, message, user=None, files=[], close_branch=False):
		"""Commit changes to the repository."""
		userspec = (['--author', user] if user else ['--author', self.user] if self.user else [])
		close = "--close-branch" if close_branch else ""
		self.git_command("commit", "-m", message, close, 
						*userspec + files)

	def git_log(self, identifier=None, limit=None, template=None, **kwargs):
		"""Get repositiory log"""
		cmds = ["log"]
		if identifier: cmds += [identifier, '-n', '1']
		if limit: cmds += ['-n', str(limit)]
		if template: cmds += [str(template)]
		if kwargs:
			for key in kwargs:
				cmds += [key, kwargs[key]]
		return self.git_command(*cmds)
		
	def git_status(self, empty=False):
		"""Get repository status.
		Returns a dict containing a *change char* -> *file list* mapping, where 
		change char is in::

		 A, M, R, !, ?

		Example - added one.txt, modified a_folder/two.txt and three.txt::

		 {'A': ['one.txt'], 'M': ['a_folder/two.txt', 'three.txt'],
		 '!': [], '?': [], 'R': []}

		If empty is set to non-False value, don't add empty lists
		"""
		out = self.git_command('status', '-s').strip()
		#default empty set
		if empty:
			changes = {}
		else:
			changes = {}
		if not out: return changes
		lines = out.split("\n")
		status_split = re.compile("^([^\s]+)\s+(.*)$")

		for change, path in [status_split.match(x.strip()).groups() for x in lines]:
			changes.setdefault(change, []).append(path)
		return changes

	def git_push(self, destination=None, branch=None):
		"""Push changes from this repo."""
		args = [arg for arg in (destination, branch) if not arg is None]
		self.git_command("push", *args)


	def git_pull(self, source=None):
		"""Pull changes to this repo."""
		if source is None:
			self.git_command("pull")
		else:
			self.git_command("pull", source)

	def git_fetch(self, source=None):
		"""Fetch changes to this repo."""
		if source is None:
			self.git_command("fetch")
		else:
			self.git_command("fetch", source)

	@classmethod
	def git_clone(cls, url, path, *args):
		"""Clone repository at given `url` to `path`,
		then return repo object to `path`."""
		Repo.command(None, "clone", url, path, *args)
		return Repo(path)
		
	rev_log_tpl = '--pretty=format:{"node":"%h","author":"%an", "parents":"%p","date":"%ci","desc":"%s"}'

	def revision(self, identifier):
		"""Get the identified revision as a Revision object"""
		out = self.git_log(identifier=identifier, template=self.rev_log_tpl)
		
		return Revision(out)

	def read_config(self):
		"""Read the configuration as seen with 'git config -l'
		Is called by __init__ - only needs to be called explicitly
		to reflect changes made since instantiation"""
		res = self.git_command("config", "-l")
		cfg = {}
		for row in res.split("\n"):
			section, ign, value = row.partition("=")
			main, ign, sub = section.partition(".")
			sect_cfg = cfg.setdefault(main, {})
			sect_cfg[sub] = value.strip()
		self.cfg = cfg
		return cfg

	def config(self, section, key):
		"""Return the value of a configuration variable"""
		if not self.cfg: 
			self.cfg = self.read_config()
		return self.cfg.get(section, {}).get(key, None)
	
	def configbool(self, section, key):
		"""Return a config value as a boolean value.
		Empty values, the string 'false' (any capitalization),
		and '0' are considered False, anything else True"""
		if not self.cfg: 
			self.cfg = self.read_config()
		value = self.cfg.get(section, {}).get(key, None)
		if not value: 
			return False
		if (value == "0" 
			or value.upper() == "FALSE"
			or value.upper() == "None"): 
			return False
		return True

	def configlist(self, section, key):
		"""Return a config value as a list; will try to create a list
		delimited by commas, or whitespace if no commas are present"""
		if not self.cfg: 
			self.cfg = self.read_config()
		value = self.cfg.get(section, {}).get(key, None)
		if not value: 
			return []
		if value.count(","):
			return value.split(",")
		else:
			return value.split()



DEPOT = os.path.dirname(os.path.dirname(os.path.abspath( __file__ )))

def setOptions(parser):
	parser.add_argument("-t", "--tool", dest="TOOL", help="Specify the TOOL to version.")
	parser.add_argument("-m", "--major", dest="MAJOR", type=int, help="Specify MAJOR version.")
	parser.add_argument("-n", "--minor", dest="MINOR", type=int, help="Specify MINOR version.")
	parser.add_argument("-c", "--comment", dest="COMMENT", help="Specify a commentary.")

parser = ArgumentParser()
setOptions(parser)
args = parser.parse_args()

def tool_dir():
	return os.path.join(DEPOT, 'tool', args.TOOL)

# Check valid tool
if not (args.TOOL and os.path.isdir(tool_dir())):
	parser.print_help()
	print "\nYou must specify a a valid tool."
	sys.exit(-1)

# Check major version
if not (args.MAJOR):
	parser.print_help()
	print "\nYou must specify a major version number."
	sys.exit(-1)

# Check minor version	
if not (args.MINOR):
	parser.print_help()
	print "\nYou must specify a minor version number."
	sys.exit(-1)

if not args.COMMENT:
	parser.print_help()
	print "\nYou must specify a comment."
	sys.exit(-1)

tag_string = "%s_v%d.%d" % (args.TOOL, args.MAJOR, args.MINOR)
version_filename = os.path.join(tool_dir(), 'version.cmake')

repo = Repo(DEPOT)
tags = repo.git_tags()
if tag_string in tags:
	print "Version already tagged on git.\nAborting!\n"
	sys.exit(-1)

print "Updating '%s'\n" % version_filename
f = open(version_filename,'w')
f.write('set( VERSION_MAJOR %d )\n' % args.MAJOR)
f.write('set( VERSION_MINOR %d )\n '% args.MINOR)
f.close()

print "Adding '%s' to git.\n" % version_filename
repo.git_add(version_filename)

#import pdb;pdb.set_trace()

if not 'M' in repo.git_status():
	print "No chages in new version.\n"
	sys.exit(-1)

commit_string = "[%s] Changed version to %d.%d: %s" % (args.TOOL, args.MAJOR, args.MINOR, args.COMMENT)
print "Git commiting: '%s'\n" % commit_string
repo.git_commit(commit_string)

print "Git tagging '%s'\n" % tag_string
repo.git_tag(tag_string, m=args.COMMENT)

print "Done!'\n"
